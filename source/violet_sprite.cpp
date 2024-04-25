#include "violet_file.hpp"
#include "violet_matrix_internal.hpp"
#include "violet_message_internal.hpp"
#include "violet_shader_internal.hpp"
#include "violet_sprite_internal.hpp"
#include "violet_texture_internal.hpp"

namespace Violet
{
    static Pointer<SpriteSheetGroup> sprite_sheet_group{ nullptr };

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

    void InitSprites()
    {
        sprite_sheet_group = new SpriteSheetGroup();

        LoadShader("sprite_internal", sprite_shader_vertex, sprite_shader_frag);
    }

    void CloseSprites()
    {
        sprite_sheet_group = nullptr;
    }

    void LoadSpriteSheet(const std::string& id, const std::string& path, const std::string& texture)
    {
        Pointer<SpriteSheet> sheet = new SpriteSheet("spr_" + id, path, texture);
        if (sheet->IsLoaded()) {
            sprite_sheet_group->Add("spr_" + id, sheet);
        }
    }

    void DestroySpriteSheet(const std::string& id)
    {
        sprite_sheet_group->Destroy("spr_" + id);
    }

    void DrawSprite(const std::string& sheet_id, const uint layer, const uint frame, Point2D<float> position,
                    const Point2D<float> scale, const float angle, const TextureFilter filter)
    {
        Pointer<SpriteSheet> sprite_sheet = sprite_sheet_group->Get("spr_" + sheet_id);
        if (sprite_sheet != nullptr) {
            sprite_sheet->QueueDraw(layer, { frame, position, scale, angle, filter });
        }
    }

    void DrawSpriteLayer(uint layer)
    {
        sprite_sheet_group->DrawLayer(layer);
    }

    SpriteSheet::SpriteSheet(const std::string& id, const std::string& path, const std::string& texture): Resource(id)
    {
        Pointer<File> file = new File(path, false);
        this->Info("Loading \"" + path + "\"");

        if (this->Error("Failed to open", !file->IsOpen())) {
            return;
        }

        if (this->Error("Not a valid sprite sheet", file->ReadString(16).compare("VIOLET SPRITE   ")) != 0) {
            return;
        }

        this->count = file->ReadUIntBE();
        if (this->Error("Failed to read sprite count", file->Failed())) {
            return;
        }

        int texture_width = GetTextureWidth(texture);
        if (this->Error("Invalid texture width " + std::to_string(texture_width), texture_width <= 0)) {
            return;
        }

        int texture_height = GetTextureHeight(texture);
        if (this->Error("Invalid texture height " + std::to_string(texture_width), texture_height <= 0)) {
            return;
        }

        this->texture               = texture;
        this->mesh                  = new Mesh(false, this->count * 4, this->count * 6, { 2, 2 });
        Pointer<float> vertex_data  = this->mesh->GetVertexBuffer();
        Pointer<uint>  element_data = this->mesh->GetElementBuffer();

        for (uint i = 0; i < this->count; i++) {
            int x = file->ReadIntBE();
            if (this->Error("Failed to read X offset for sprite " + std::to_string(i), file->Failed())) {
                return;
            }

            int y = file->ReadIntBE();
            if (this->Error("Failed to read Y offset for sprite " + std::to_string(i), file->Failed())) {
                return;
            }

            int width = file->ReadIntBE();
            if (this->Error("Failed to read width for sprite " + std::to_string(i), file->Failed())) {
                return;
            }
            else if (this->Error("Invalid width " + std::to_string(width) + " for sprite " + std::to_string(i), width < 0)) {
                return;
            }

            int height = file->ReadIntBE();
            if (this->Error("Failed to read height for sprite " + std::to_string(i), file->Failed())) {
                return;
            }
            else if (this->Error("Invalid height " + std::to_string(width) + " for sprite " + std::to_string(i), height < 0)) {
                return;
            }

            int pivot_x = file->ReadIntBE();
            if (this->Error("Failed to read pivot X offset for sprite " + std::to_string(i), file->Failed())) {
                return;
            }

            int pivot_y = file->ReadIntBE();
            if (this->Error("Failed to read pivot Y offset for sprite " + std::to_string(i), file->Failed())) {
                return;
            }

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

        this->loaded = true;
        this->Info("Loaded successfully");
    }

    void SpriteSheet::QueueDraw(const uint layer, const SpriteDraw& sprite)
    {
        if (layer < 256 && sprite.frame < this->count) {
            this->draw_queue[layer].push_back(sprite);
        } else {
            this->Error("Attempted to draw invalid sprite " + std::to_string(sprite.frame));
        }
    }
    
    void SpriteSheet::DrawLayer(const uint layer)
    {
        if (layer < 256) {
            for (int i = 0; i < this->draw_queue[layer].size(); i++) {
                const SpriteDraw& sprite = this->draw_queue[layer][i];
                
                SetTextureFilter(this->texture, sprite.filter);
                AttachShader("sprite_internal");
                SetShaderMatrix4x4("inProjection", false, 1, glm::value_ptr(Get2dProjectionMatrix()));
                SetShaderMatrix4x4("inTransform", false, 1,
                    glm::value_ptr(Get2dTransformMatrix(sprite.position, sprite.scale, sprite.angle)));
                SetShaderTexture(this->texture, 0);

                this->mesh->DrawPartial(2, sprite.frame * 2);
            }

            this->draw_queue[layer].clear();
        }
    }

    void SpriteSheetGroup::DrawLayer(const uint layer)
    {
        if (layer < 256) {
            for (auto sprite_sheet : this->resources) {
                sprite_sheet.second->DrawLayer(layer);
            }
        }
    }
}