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
        UIVector2 texture_size = GetTextureSize(texture);

        if (!file->IsOpen()) {
            LogError("Failed to open sprite sheet \"" + this->id + "\"");
        } else if (file->ReadString(16).compare("VIOLET SPRITE   ") != 0) {
            LogError("Invalid file for sprite sheet \"" + this->id + "\"");
        } else if (texture_size.X() == 0 || texture_size.Y() == 0) {
            LogError("Invalid size " + std::to_string(texture_size.X()) + "x" + std::to_string(texture_size.Y()) + " from texture " + texture);
        } else {
            this->count = file->ReadUIntBE();

            if (file->Failed()) {
                LogError("Failed to read sprite count for sprite sheet \"" + this->id + "\"");
            } else {
                this->texture               = texture;
                this->mesh                  = new Mesh(false, this->count * 4, this->count * 6, { 2, 2 });
                Pointer<float> vertex_data  = this->mesh->GetVertexBuffer();
                Pointer<uint>  element_data = this->mesh->GetElementBuffer();

                for (uint i = 0; i < this->count; i++) {
                    bool frame_success = true;
            
                    uint x = file->ReadUIntBE();
                    frame_success &= !file->Failed();

                    uint y = file->ReadUIntBE();
                    frame_success &= !file->Failed();

                    uint width = file->ReadUIntBE();
                    frame_success &= !file->Failed();

                    uint height = file->ReadUIntBE();
                    frame_success &= !file->Failed();

                    int pivot_x = file->ReadIntBE();
                    frame_success &= !file->Failed();

                    int pivot_y = file->ReadIntBE();
                    frame_success &= !file->Failed();

                    if (!frame_success) {
                        LogError("Failed to read sprite " + std::to_string(i) + " for sprite sheet \"" + this->id + "\"");

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
                    } else {
                        *(vertex_data++) = -pivot_x;
                        *(vertex_data++) = -pivot_y;
                        *(vertex_data++) = x / static_cast<float>(texture_size.X());
                        *(vertex_data++) = y / static_cast<float>(texture_size.Y());

                        *(vertex_data++) = -pivot_x + width;
                        *(vertex_data++) = -pivot_y;
                        *(vertex_data++) = (x + width) / static_cast<float>(texture_size.X());
                        *(vertex_data++) = y / static_cast<float>(texture_size.Y());

                        *(vertex_data++) = -pivot_x;
                        *(vertex_data++) = -pivot_y + height;
                        *(vertex_data++) = x / static_cast<float>(texture_size.X());
                        *(vertex_data++) = (y + height) / static_cast<float>(texture_size.Y());

                        *(vertex_data++) = -pivot_x + width;
                        *(vertex_data++) = -pivot_y + height;
                        *(vertex_data++) = (x + width) / static_cast<float>(texture_size.X());
                        *(vertex_data++) = (y + height) / static_cast<float>(texture_size.Y());
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
        if (GetSpriteSheet(id) == nullptr) {
            Pointer<SpriteSheet> sprite_sheet = new SpriteSheet(id, path, texture);

            if (sprite_sheet->loaded) {
                sprite_sheet_group->sprite_sheets.insert({ id, sprite_sheet });
            }
        } else {
            LogError("LoadSpriteSheet: \"" + id + "\" is already loaded");
        }
    }

    void DestroySpriteSheet(const std::string& id)
    {
        if (GetSpriteSheet(id) != nullptr) {
            sprite_sheet_group->sprite_sheets.erase(id);
        } else {
            LogError("DestroySpriteSheet: \"" + id + "\" doesn't exist");
        }
    }

    void DestroyAllSpriteSheets()
    {
        sprite_sheet_group->sprite_sheets.clear();
    }

    void DrawSprite(const std::string& id, const uint layer, const uint frame, const Vector2& pos, const float angle, const Vector2& scale)
    {
        Pointer<SpriteSheet> sprite_sheet = GetSpriteSheet(id);

        if (sprite_sheet != nullptr) {
            if (frame < sprite_sheet->count) {
                sprite_sheet->draw_queue[layer].push_back({ frame, pos, Math::Radians(angle), scale });
            } else {
                LogError("DrawSprite: Attempted to draw invalid sprite " + std::to_string(frame) + " from " + "\"" + sprite_sheet->id + "\"");
            }
        } else {
            LogError("DrawSprite: \"" + id + "\" doesn't exist");
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