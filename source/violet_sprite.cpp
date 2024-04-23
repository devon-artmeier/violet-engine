#include "violet_message_internal.hpp"
#include "violet_sprite_internal.hpp"

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
                int version = file->ReadUChar();
                if (file->Failed()) {
#ifdef VIOLET_DEBUG
                    LogError("Failed to read version number from \"" + path + "\"");
#endif
                    return;
                }
                if (version != 1) {
#ifdef VIOLET_DEBUG
                    LogError("Invalid sprite sheet version \"" + std::to_string(version) + "\" in \"" + path + "\"");
#endif
                    return;
                }

                if (this->ReadFile(file, path)) {
                    this->texture = texture;
                    this->mesh    = new Mesh(false, 0, 0, {2, 2});
                    this->loaded  = true;
                }
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
        
    }

    bool SpriteSheet::ReadFile(const Pointer<File>& file, const std::string& path)
    {
        uint read_count = file->ReadUIntBE();
        if (file->Failed()) {
#ifdef VIOLET_DEBUG
            LogError("Failed to read sprite count from \"" + path + "\"");
#endif
            return false;
        }



        this->count = read_count;
        return true;
    }
}