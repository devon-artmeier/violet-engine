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
        LogInfo("Loading sprite sheet \"" + this->id + "\" from file \"" + path + "\"");

        Pointer<File> file = new File(path, false);

        if (Assert(file->IsOpen(), "Failed to open sprite sheet \"" + this->id + "\"") &&
            Assert(file->ReadString(16).compare("VIOLET SPRITE   ") == 0, "Invalid file for sprite sheet \"" + this->id + "\"")) {
            bool header_success = true;

            uint texture_width = GetTextureWidth(texture);
            header_success &= Assert(texture_width != 0, "Invalid width " + std::to_string(texture_width) + " from texture " + texture);

            uint texture_height = GetTextureHeight(texture);
            header_success &= Assert(texture_height != 0, "Invalid height " + std::to_string(texture_width) + " from texture " + texture);

            this->count = file->ReadUIntBE();
            header_success &= Assert(!file->Failed(), "Failed to read sprite count for sprite sheet \"" + this->id + "\"");

            if (header_success) {
                this->texture               = texture;
                this->mesh                  = new Mesh(false, this->count * 4, this->count * 6, { 2, 2 });
                Pointer<float> vertex_data  = this->mesh->GetVertexBuffer();
                Pointer<uint>  element_data = this->mesh->GetElementBuffer();

                for (uint i = 0; i < this->count; i++) {
                    bool frame_success = true;
            
                    uint x = file->ReadUIntBE();
                    frame_success &= Assert(!file->Failed(), "Failed to read X offset for sprite " + std::to_string(i) + " for sprite sheet \"" + this->id + "\"");

                    uint y = file->ReadUIntBE();
                    frame_success &= Assert(!file->Failed(), "Failed to read Y offset for sprite " + std::to_string(i) + " for sprite sheet \"" + this->id + "\"");

                    uint width = file->ReadUIntBE();
                    frame_success &= Assert(!file->Failed(), "Failed to read width for sprite " + std::to_string(i) + " for sprite sheet \"" + this->id + "\"");

                    uint height = file->ReadUIntBE();
                    frame_success &= Assert(!file->Failed(), "Failed to read height for sprite " + std::to_string(i) + " for sprite sheet \"" + this->id + "\"");

                    int pivot_x = file->ReadIntBE();
                    frame_success &= Assert(!file->Failed(), "Failed to read pivot X offset for sprite " + std::to_string(i) + " for sprite sheet \"" + this->id + "\"");

                    int pivot_y = file->ReadIntBE();
                    frame_success &= Assert(!file->Failed(), "Failed to read pivot Y offset for sprite " + std::to_string(i) + " for sprite sheet \"" + this->id + "\"");

                    if (frame_success) {
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
                    } else {
                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;

                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;

                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;

                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;
                        *(vertex_data++) = 0;
                    }

                    *(element_data++) = 0;
                    *(element_data++) = 1;
                    *(element_data++) = 2;
                    *(element_data++) = 1;
                    *(element_data++) = 2;
                    *(element_data++) = 3;
                }

                this->mesh->RefreshVertexBuffer();
                this->mesh->RefreshElementBuffer();

                LogInfo("Loaded sprite sheet \"" + this->id + "\" successfully");
                this->loaded = true;
            }
        }
    }

    SpriteSheet::~SpriteSheet()
    {
        LogInfo("Destroyed sprite sheet \"" + this->id + "\"");
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
        if (Assert(GetSpriteSheet(id) == nullptr, "LoadSpriteSheet: \"" + id + "\" is already loaded")) {
            Pointer<SpriteSheet> sprite_sheet = new SpriteSheet(id, path, texture);

            if (sprite_sheet->loaded) {
                sprite_sheet_group->sprite_sheets.insert({ id, sprite_sheet });
            }
        }
    }

    void DestroySpriteSheet(const std::string& id)
    {
        if (Assert(GetSpriteSheet(id) != nullptr, "DestroySpriteSheet: \"" + id + "\" doesn't exist")) {
            sprite_sheet_group->sprite_sheets.erase(id);
        }
    }

    void DestroyAllSpriteSheets()
    {
        sprite_sheet_group->sprite_sheets.clear();
    }

    void DrawSprite(const std::string& id, const uint layer, const uint frame, const Vector2& pos, const float angle, const Vector2& scale)
    {
        Pointer<SpriteSheet> sprite_sheet = GetSpriteSheet(id);

        if (Assert(sprite_sheet != nullptr, "DrawSprite: \"" + id + "\" doesn't exist")) {
            if (Assert(frame < sprite_sheet->count, "DrawSprite: Attempted to draw invalid sprite " + std::to_string(frame) + " from " + "\"" + sprite_sheet->id + "\"")) {
                sprite_sheet->draw_queue[layer].push_back({ frame, pos, Math::Radians(angle), scale });
            }
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