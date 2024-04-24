#ifndef VIOLET_ENGINE_SPRITE_INTERNAL_HPP
#define VIOLET_ENGINE_SPRITE_INTERNAL_HPP

#include "violet_file.hpp"
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
            
            void Draw(uint frame);

        private:
            std::string   texture{ "" };
            Pointer<Mesh> mesh   { nullptr };
            bool          loaded { false };
            uint          count  { 0 };
    };
    
    extern void InitSpriteSheetGroup ();
    extern void CloseSpriteSheetGroup();
}

#endif // VIOLET_ENGINE_SPRITE_INTERNAL_HPP