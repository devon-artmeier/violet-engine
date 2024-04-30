#include "violet_engine_internal.hpp"

namespace Violet
{
    void DrawSprite(const std::string& sprite_sheet_id, const uint layer, const uint frame, const float x, const float y)
    {
        DrawSprite(sprite_sheet_id, layer, frame, x, y, 1.0f, 1.0f, 0.0f);
    }

    void DrawSprite(const std::string& sprite_sheet_id, const uint layer, const uint frame, const float x, const float y,
                    const float x_scale, const float y_scale, const float angle)
    {
        Pointer<SpriteSheet> sprite_sheet = GetSpriteSheet(sprite_sheet_id);
        if (sprite_sheet != nullptr) {
            sprite_sheet->QueueDraw(layer, { frame, x, y, x_scale, y_scale, angle });
        }
    }

    void DrawSpriteLayer(uint layer)
    {
        if (layer < 256) {
            for (auto sprite_sheet : GetAllSpriteSheets()) {
                sprite_sheet.second->DrawLayer(layer);
            }
        }
    }

    SpriteSheet::SpriteSheet(const std::string& id, const std::string& path, const std::string& texture)
    {
        this->id = id;

        Pointer<File> file = new File(path, false);
#ifdef VIOLET_DEBUG
        LogInfo(this->id + ": Loading \"" + path + "\"");
#endif

        if (!file->IsOpen()) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Failed to open");
#endif
            return;
        }

        if (file->ReadString(16).compare("VIOLET SPRITE   ") != 0) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Not a valid sprite sheet");
#endif
            return;
        }

        this->count = file->ReadUIntBE();
        if (file->Failed()) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Failed to read sprite count");
#endif
            return;
        }

        int texture_width = GetTextureWidth(texture);
        if (texture_width <= 0) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Invalid texture width " + std::to_string(texture_width) + " from texture " + texture);
#endif
            return;
        }

        int texture_height = GetTextureHeight(texture);
        if (texture_height <= 0) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Invalid texture height " + std::to_string(texture_height) + " from texture " + texture);
#endif
            return;
        }

        this->texture               = texture;
        this->mesh                  = new Mesh(false, this->count * 4, this->count * 6, { 2, 2 });
        Pointer<float> vertex_data  = this->mesh->GetVertexBuffer();
        Pointer<uint>  element_data = this->mesh->GetElementBuffer();

        for (uint i = 0; i < this->count; i++) {
            int x = file->ReadIntBE();
            if (file->Failed()) {
#ifdef VIOLET_DEBUG
                LogError(this->id + ": Failed to read X offset for sprite " + std::to_string(i));
#endif
                return;
            }

            int y = file->ReadIntBE();
            if (file->Failed()) {
#ifdef VIOLET_DEBUG
                LogError(this->id + ": Failed to read Y offset for sprite " + std::to_string(i));
#endif
                return;
            }

            int width = file->ReadIntBE();
            if (file->Failed()) {
#ifdef VIOLET_DEBUG
                LogError(this->id + ": Failed to read width for sprite " + std::to_string(i));
#endif
                return;
            } else if (width < 0) {
#ifdef VIOLET_DEBUG
                LogError(this->id + ": Invalid width " + std::to_string(width) + " for sprite " + std::to_string(i));
#endif
                return;
            }

            int height = file->ReadIntBE();
            if (file->Failed()) {
#ifdef VIOLET_DEBUG
                LogError(this->id + ": Failed to read height for sprite " + std::to_string(i));
#endif
                return;
            } else if (height < 0) {
#ifdef VIOLET_DEBUG
                LogError(this->id + ": Invalid height " + std::to_string(height) + " for sprite " + std::to_string(i));
#endif
                return;
            }

            int pivot_x = file->ReadIntBE();
            if (file->Failed()) {
#ifdef VIOLET_DEBUG
                LogError(this->id + ": Failed to read pivot X offset for sprite " + std::to_string(i));
#endif
                return;
            }

            int pivot_y = file->ReadIntBE();
            if (file->Failed()) {
#ifdef VIOLET_DEBUG
                LogError(this->id + ": Failed to read pivot Y offset for sprite " + std::to_string(i));
#endif
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
#ifdef VIOLET_DEBUG
        LogInfo(this->id + ": Loaded successfully");
#endif
    }

    SpriteSheet::~SpriteSheet()
    {
#ifdef VIOLET_DEBUG
        LogInfo(this->id + ": Destroyed");
#endif
    }

    bool SpriteSheet::IsLoaded() const
    {
        return this->loaded;
    }

    void SpriteSheet::QueueDraw(const uint layer, const SpriteDraw& draw)
    {
        if (layer < 256) {
            if (draw.frame < this->count) {
                this->draw_queue[layer].push_back(draw);
            } else {
#ifdef VIOLET_DEBUG
                LogError(this->id + ": Attempted to draw invalid sprite " + std::to_string(draw.frame));
#endif
            }
        }
    }
    
    void SpriteSheet::DrawLayer(const uint layer)
    {
        if (layer < 256) {
            for (int i = 0; i < this->draw_queue[layer].size(); i++) {
                const SpriteDraw& draw = this->draw_queue[layer][i];
                
                AttachShader("shader_sprite_internal");
                SetShaderMatrix4x4("inProjection", false, 1, glm::value_ptr(Get2dProjectionMatrix()));
                SetShaderMatrix4x4("inTransform", false, 1,
                    glm::value_ptr(Get2dTransformMatrix(draw.x, draw.y, draw.x_scale, draw.y_scale, draw.angle)));
                SetShaderTexture(this->texture, 0);

                this->mesh->DrawPartial(2, draw.frame * 2);
            }
            this->draw_queue[layer].clear();
        }
    }
}