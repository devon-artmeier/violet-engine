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
        this->texture = texture;
        this->mesh    = new Mesh(false, 0, 0, {2, 2});
    }

    SpriteSheet::~SpriteSheet()
    {
        
    }
}