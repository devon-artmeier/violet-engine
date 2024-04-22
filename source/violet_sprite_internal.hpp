#ifndef VIOLET_ENGINE_SPRITE_INTERNAL_HPP
#define VIOLET_ENGINE_SPRITE_INTERNAL_HPP

#include "violet_mesh_internal.hpp"
#include "violet_resource.hpp"
#include "violet_sprite.hpp"

namespace Violet
{
    class SpriteSheet : public Resource
    {
        public:
            SpriteSheet(const std::string& id, const std::string& path, const std::string& texture);
            ~SpriteSheet();

        private:
            std::string   texture{ "" };
            Pointer<Mesh> mesh   { nullptr };
            bool          loaded { false };
    };
    
    extern void InitSpriteSheetGroup ();
    extern void CloseSpriteSheetGroup();
}

#endif // VIOLET_ENGINE_SPRITE_INTERNAL_HPP