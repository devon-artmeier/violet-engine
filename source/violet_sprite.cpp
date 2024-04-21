#include "violet_message_internal.hpp"
#include "violet_sprite_internal.hpp"

namespace Violet
{
    static SpriteSheetManager* sprite_sheet_manager{ nullptr };

    void InitSpriteSheetManager()
    {
        sprite_sheet_manager = new SpriteSheetManager();
    }

    void CloseSpriteSheetManager()
    {
        delete sprite_sheet_manager;
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

    SpriteSheetManager::~SpriteSheetManager()
    {
        this->DestroyAllSpriteSheets();
    }

    SpriteSheet* SpriteSheetManager::GetSpriteSheet(const std::string& id) const
    {
        auto sheet = this->sheets.find(id);
        if (sheet != this->sheets.end()) {
            return sheet->second;
        }
        return nullptr;
    }

    void SpriteSheetManager::AddSpriteSheet(const std::string& id, SpriteSheet* sheet)
    {
        this->DestroySpriteSheet(id);
        this->sheets.insert({id, sheet});
    }
    
    void SpriteSheetManager::DestroySpriteSheet(const std::string& id)
    {
        SpriteSheet* sheet = GetSpriteSheet(id);
        if (sheet != nullptr) {
            delete sheet;
            this->sheets.erase(id);
        }
    }
    
    void SpriteSheetManager::DestroyAllSpriteSheets()
    {
        for (auto sheet : this->sheets) {
            delete sheet.second;
        }
        this->sheets.clear();
    }
}