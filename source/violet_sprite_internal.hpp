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
            bool        loaded { false };
    };

    class SpriteSheetGroup
    {
        public:
            ~SpriteSheetGroup();

            SpriteSheet* GetSpriteSheet        (const std::string& id) const;
            void         AddSpriteSheet        (const std::string& id, SpriteSheet* sheet);
            void         DestroySpriteSheet    (const std::string& id);
            void         DestroyAllSpriteSheets();

        private:
            std::unordered_map<std::string, SpriteSheet*> sheets;
    };
    
    extern void InitSpriteSheetGroup ();
    extern void CloseSpriteSheetGroup();
}

#endif // VIOLET_ENGINE_SPRITE_INTERNAL_HPP