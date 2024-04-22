#include "violet_message_internal.hpp"
#include "violet_sprite_internal.hpp"

namespace Violet
{
    static SpriteSheetGroup* sprite_sheet_group{ nullptr };

    void InitSpriteSheetGroup()
    {
        sprite_sheet_group = new SpriteSheetGroup();
    }

    void CloseSpriteSheetGroup()
    {
        delete sprite_sheet_group;
    }

    SpriteSheet::SpriteSheet(const std::string& id, const std::string& path, const std::string& texture)
    {
        this->id      = id;
        this->texture = texture;
        this->mesh    = new Mesh(false, 0, 0, {2, 2});
    }

    SpriteSheet::~SpriteSheet()
    {
        delete this->mesh;
    }

    SpriteSheetGroup::~SpriteSheetGroup()
    {
        this->DestroyAllSpriteSheets();
    }

    SpriteSheet* SpriteSheetGroup::GetSpriteSheet(const std::string& id) const
    {
        auto sheet = this->sheets.find(id);
        if (sheet != this->sheets.end()) {
            return sheet->second;
        }
        return nullptr;
    }

    void SpriteSheetGroup::AddSpriteSheet(const std::string& id, SpriteSheet* sheet)
    {
        this->DestroySpriteSheet(id);
        this->sheets.insert({id, sheet});
    }
    
    void SpriteSheetGroup::DestroySpriteSheet(const std::string& id)
    {
        SpriteSheet* sheet = GetSpriteSheet(id);
        if (sheet != nullptr) {
            delete sheet;
            this->sheets.erase(id);
        }
    }
    
    void SpriteSheetGroup::DestroyAllSpriteSheets()
    {
        for (auto sheet : this->sheets) {
            delete sheet.second;
        }
        this->sheets.clear();
    }
}