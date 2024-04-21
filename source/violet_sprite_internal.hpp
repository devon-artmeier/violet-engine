#ifndef VIOLET_ENGINE_SPRITE_INTERNAL_HPP
#define VIOLET_ENGINE_SPRITE_INTERNAL_HPP

#include "violet_mesh_internal.hpp"
#include "violet_sprite.hpp"

namespace Violet
{
    class SpriteSheet
    {
        public:
            SpriteSheet(const std::string& id, const std::string& path, const std::string& texture);
            ~SpriteSheet();

        private:
            std::string id     { "" };
            std::string texture{ "" };
            Mesh*       mesh   { nullptr };
    };

    class SpriteSheetManager
    {
        public:
            ~SpriteSheetManager();

            SpriteSheet* GetSpriteSheet        (const std::string& id) const;
            void         AddSpriteSheet        (const std::string& id, SpriteSheet* sheet);
            void         DestroySpriteSheet    (const std::string& id);
            void         DestroyAllSpriteSheets();

        private:
            std::unordered_map<std::string, SpriteSheet*> sheets;
    };
    
    extern void InitSpriteSheetManager ();
    extern void CloseSpriteSheetManager();
}

#endif // VIOLET_ENGINE_SPRITE_INTERNAL_HPP