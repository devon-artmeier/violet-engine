#include "violet_engine_internal.hpp"

namespace Violet
{
    static const char* sprite_shader_vertex =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec2 inVecCoord;\n"
        "layout (location = 1) in vec2 inTexCoord;\n"
        "\n"
        "uniform mat4 inProjection;\n"
        "uniform mat4 inTransform;\n"
        "out vec2 fragTexCoord;\n"
        "\n"
        "void main()\n"
        "{\n"
        "	gl_Position = inProjection * inTransform * vec4(inVecCoord, 0.0f, 1.0f);\n"
        "	fragTexCoord = inTexCoord;\n"
        "}";

    static const char* sprite_shader_frag =
        "#version 330 core\n"
        "\n"
        "in vec2 fragTexCoord;\n"
        "uniform sampler2D fragTexture;\n"
        "out vec4 outColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "	outColor = texture(fragTexture, fragTexCoord);\n"
        "}";

    class SpriteSheetGroup
    {
        public:
            std::unordered_map<std::string, Pointer<SpriteSheet>> sprite_sheets;
    };
    
    static Pointer<SpriteSheetGroup> sprite_sheet_group{ nullptr };
    static Pointer<Shader>           sprite_shader     { nullptr };

    SpriteSheet::SpriteSheet(const std::string& id, const std::string& path, const std::string& texture)
    {
        this->id = id;
        LogInfo(this->id + ": Loading \"" + path + "\"");

        Pointer<File> file = new File(path, false);
        Assert(file->IsOpen(), this->id + ": Failed to open \"" + path + "\"");

        Assert(file->ReadString(16).compare("VIOLET SPRITE   ") == 0, this->id + ": Not a valid sprite sheet");

        this->count = file->ReadUIntBE();
        Assert(!file->Failed(), this->id + ": Failed to read sprite count");

        uint texture_width = GetTextureWidth(texture);
        Assert(texture_width != 0, this->id + ": Invalid texture width " + std::to_string(texture_width) + " from texture " + texture);

        uint texture_height = GetTextureHeight(texture);
        Assert(texture_height != 0, this->id + ": Invalid texture height " + std::to_string(texture_width) + " from texture " + texture);

        this->texture               = texture;
        this->mesh                  = new Mesh(false, this->count * 4, this->count * 6, { 2, 2 });
        Pointer<float> vertex_data  = this->mesh->GetVertexBuffer();
        Pointer<uint>  element_data = this->mesh->GetElementBuffer();

        for (uint i = 0; i < this->count; i++) {
            uint x = file->ReadUIntBE();
            Assert(!file->Failed(), this->id + ": Failed to read X offset for sprite " + std::to_string(i));

            uint y = file->ReadUIntBE();
            Assert(!file->Failed(), this->id + ": Failed to read Y offset for sprite " + std::to_string(i));

            uint width = file->ReadUIntBE();
            Assert(!file->Failed(), this->id + ": Failed to read width for sprite " + std::to_string(i));

            uint height = file->ReadUIntBE();
            Assert(!file->Failed(), this->id + ": Failed to read height for sprite " + std::to_string(i));

            int pivot_x = file->ReadIntBE();
            Assert(!file->Failed(), this->id + ": Failed to read pivot X offset for sprite " + std::to_string(i));

            int pivot_y = file->ReadIntBE();
            Assert(!file->Failed(), this->id + ": Failed to read pivot Y offset for sprite " + std::to_string(i));

            *(vertex_data++) = -pivot_x;
            *(vertex_data++) = -pivot_y;
            *(vertex_data++) = x / static_cast<float>(texture_width);
            *(vertex_data++) = y / static_cast<float>(texture_height);

            *(vertex_data++) = -pivot_x + width;
            *(vertex_data++) = -pivot_y;
            *(vertex_data++) = (x + width) / static_cast<float>(texture_width);
            *(vertex_data++) = y / static_cast<float>(texture_height);

            *(vertex_data++) = -pivot_x;
            *(vertex_data++) = -pivot_y + height;
            *(vertex_data++) = x / static_cast<float>(texture_width);
            *(vertex_data++) = (y + height) / static_cast<float>(texture_height);

            *(vertex_data++) = -pivot_x + width;
            *(vertex_data++) = -pivot_y + height;
            *(vertex_data++) = (x + width) / static_cast<float>(texture_width);
            *(vertex_data++) = (y + height) / static_cast<float>(texture_height);

            *(element_data++) = 0;
            *(element_data++) = 1;
            *(element_data++) = 2;
            *(element_data++) = 1;
            *(element_data++) = 2;
            *(element_data++) = 3;
        }

        this->mesh->RefreshVertexBuffer();
        this->mesh->RefreshElementBuffer();

        LogInfo(this->id + ": Loaded successfully");
    }

    SpriteSheet::~SpriteSheet()
    {
        LogInfo(this->id + ": Destroyed");
    }

    void InitSpriteSheetGroup()
    {
        sprite_shader      = new Shader("Default Sprite Shader", sprite_shader_vertex, sprite_shader_frag);
        sprite_sheet_group = new SpriteSheetGroup();
    }

    void DestroySpriteSheetGroup()
    {
        sprite_sheet_group = nullptr;
        sprite_shader      = nullptr;
    }

    static Pointer<SpriteSheet> GetSpriteSheet(const std::string& id)
    {
        auto sprite_sheet = sprite_sheet_group->sprite_sheets.find(id);
        if (sprite_sheet != sprite_sheet_group->sprite_sheets.end()) {
            return sprite_sheet->second;
        }
        return nullptr;
    }

    void LoadSpriteSheet(const std::string& id, const std::string& path, const std::string& texture)
    {
        if (GetSpriteSheet(id) == nullptr) {
            sprite_sheet_group->sprite_sheets.insert({ id, new SpriteSheet(id, path, texture) });
        }
    }

    void DestroySpriteSheet(const std::string& id)
    {
        const Pointer<SpriteSheet>& sprite_sheet = GetSpriteSheet(id);
        if (sprite_sheet != nullptr) {
            sprite_sheet_group->sprite_sheets.erase(id);
        }
    }

    void DestroyAllSpriteSheets()
    {
        sprite_sheet_group->sprite_sheets.clear();
    }

    void DrawSprite(const std::string& sprite_sheet_id, const uint layer, const uint frame, const Vector2& pos,
                    const float angle, const Vector2& scale)
    {
        Pointer<SpriteSheet> sprite_sheet = GetSpriteSheet(sprite_sheet_id);
        if (sprite_sheet != nullptr) {
            Assert(frame < sprite_sheet->count, sprite_sheet->id + ": Attempted to draw invalid sprite " + std::to_string(frame));
            sprite_sheet->draw_queue[layer].push_back({ frame, pos, Math::Radians(angle), scale });
        }
    }

    void DrawSpriteLayer(uint layer)
    {
        if (layer < 256) {
            for (auto sprite_sheet_pair : sprite_sheet_group->sprite_sheets) {
                Pointer<SpriteSheet> sprite_sheet = sprite_sheet_pair.second;

                for (int i = 0; i < sprite_sheet->draw_queue[layer].size(); i++) {
                    const SpriteDraw& draw = sprite_sheet->draw_queue[layer][i];
                
                    sprite_shader->Attach();
                    SetShaderMatrix4x4("inProjection", Get2dProjectionMatrix());
                    SetShaderMatrix4x4("inTransform", TransformMatrix(draw.pos, draw.angle, draw.scale));
                    SetShaderTexture(sprite_sheet->texture, 0);

                    sprite_sheet->mesh->DrawPartial(2, draw.frame * 2);
                }

                sprite_sheet->draw_queue[layer].clear();
            }
        }
    }
}