#include "violet_message_internal.hpp"
#include "violet_sprite_internal.hpp"
#include "violet_texture_internal.hpp"

namespace Violet
{
    static Pointer<ResourceGroup<SpriteSheet>> sprite_sheet_group{ nullptr };

    void InitSpriteSheetGroup()
    {
        sprite_sheet_group = new ResourceGroup<SpriteSheet>();
    }

    void CloseSpriteSheetGroup()
    {
        sprite_sheet_group = nullptr;
    }

    SpriteSheet::SpriteSheet(const std::string& id, const std::string& path, const std::string& texture): Resource(id)
    {
        Pointer<File> file = new File(path, false);

        if (file->IsOpen()) {
            if (file->ReadString(16).compare("VIOLET SPRITE   ") == 0) {
                this->count = file->ReadUIntBE();
                if (file->Failed()) {
#ifdef VIOLET_DEBUG
                    LogError("Failed to read sprite count from \"" + path + "\"");
#endif
                    return;
                }
                
                this->mesh = new Mesh(false, this->count * 4, this->count * 6, {2, 2});
                
                int texture_width  = GetTextureWidth(texture);
                if (texture_width <= 0) {
#ifdef VIOLET_DEBUG
                    LogError("Invalid texture width " + std::to_string(texture_width) + " from texture \"" + texture + "\"");
#endif
                    return;
                }
                
                int texture_height = GetTextureHeight(texture);
                if (texture_height <= 0) {
#ifdef VIOLET_DEBUG
                    LogError("Invalid texture height " + std::to_string(texture_height) + " from texture \"" + texture + "\"");
#endif
                    return;
                }
                
                Pointer<float> vertex_data  = this->mesh->GetVertexBuffer();
                Pointer<uint>  element_data = this->mesh->GetElementBuffer();
            
                for (uint i = 0; i < this->count; i++) {
                    int x = file->ReadIntBE();
                    if (file->Failed()) {
#ifdef VIOLET_DEBUG
                        LogError("Failed to read X value for sprite " + std::to_string(i) + " from \"" + path + "\"");
#endif
                        return;
                    }
                    
                    int y = file->ReadIntBE();
                    if (file->Failed()) {
#ifdef VIOLET_DEBUG
                        LogError("Failed to read Y value for sprite " + std::to_string(i) + " from \"" + path + "\"");
#endif
                        return;
                    }
                    
                    int width = file->ReadIntBE();
                    if (file->Failed()) {
#ifdef VIOLET_DEBUG
                        LogError("Failed to read width for sprite " + std::to_string(i) + " from \"" + path + "\"");
#endif
                        return;
                    }
                    if (width < 0) {
#ifdef VIOLET_DEBUG
                        LogError("Invalid width " + std::to_string(width) + " for sprite " + std::to_string(i) + " from \"" + path + "\"");
#endif
                        return;
                    }
                    
                    int height = file->ReadIntBE();
                    if (file->Failed()) {
#ifdef VIOLET_DEBUG
                        LogError("Failed to read height for sprite " + std::to_string(i) + " from \"" + path + "\"");
#endif
                        return;
                    }
                    if (height < 0) {
#ifdef VIOLET_DEBUG
                        LogError("Invalid height " + std::to_string(height) + " for sprite " + std::to_string(i) + " from \"" + path + "\"");
#endif
                        return;
                    }
                    
                    int pivot_x = file->ReadIntBE();
                    if (file->Failed()) {
#ifdef VIOLET_DEBUG
                        LogError("Failed to read pivot X value for sprite " + std::to_string(i) + " from \"" + path + "\"");
#endif
                        return;
                    }
                    
                    int pivot_y = file->ReadIntBE();
                    if (file->Failed()) {
#ifdef VIOLET_DEBUG
                        LogError("Failed to read pivot Y value for sprite " + std::to_string(i) + " from \"" + path + "\"");
#endif
                        return;
                    }
                    
                    *(vertex_data++)  = -pivot_x;
                    *(vertex_data++)  = -pivot_y;
                    *(vertex_data++)  = x / static_cast<float>(texture_width);
                    *(vertex_data++)  = y / static_cast<float>(texture_height);
                    
                    *(vertex_data++)  = -pivot_x + width;
                    *(vertex_data++)  = -pivot_y;
                    *(vertex_data++)  = (x + width) / static_cast<float>(texture_width);
                    *(vertex_data++)  = y / static_cast<float>(texture_height);
                    
                    *(vertex_data++)  = -pivot_x;
                    *(vertex_data++)  = -pivot_y + height;
                    *(vertex_data++)  = x / static_cast<float>(texture_width);
                    *(vertex_data++)  = (y + height) / static_cast<float>(texture_height);
                    
                    *(vertex_data++)  = -pivot_x + width;
                    *(vertex_data++)  = -pivot_y + height;
                    *(vertex_data++)  = (x + width) / static_cast<float>(texture_width);
                    *(vertex_data++)  = (y + height) / static_cast<float>(texture_height);
                    
                    *(element_data++) = 0;
                    *(element_data++) = 1;
                    *(element_data++) = 2;
                    *(element_data++) = 1;
                    *(element_data++) = 2;
                    *(element_data++) = 3;
                }
                
                this->mesh->RefreshVertexBuffer();
                this->mesh->RefreshElementBuffer();
                
                this->texture = texture;
                this->loaded  = true; 
#ifdef VIOLET_DEBUG
                LogInfo("Loaded sprite sheet \"" + id + "\" from \"" + path + "\"");
#endif
            } else {
#ifdef VIOLET_DEBUG
                LogError("\"" + path + "\" is not a valid sprite sheet file");
#endif
            }  
        } else {
#ifdef VIOLET_DEBUG
            LogError("Failed to open sprite sheet \"" + id + "\" from \"" + path + "\"");
#endif
        }
    }

    SpriteSheet::~SpriteSheet()
    {
#ifdef VIOLET_DEBUG
        LogInfo("Destroyed sprite sheet \"" + id + "\"");
#endif
    }
    
    void SpriteSheet::Draw(uint frame)
    {
        if (frame < this->count) {
            this->mesh->DrawPartial(2, frame * 2);
        } else {
#ifdef VIOLET_DEBUG
            LogError("Attempted to draw invalid sprite " + std::to_string(frame) + " from sprite sheet \"" + id + "\"");
#endif 
        }
    }
}