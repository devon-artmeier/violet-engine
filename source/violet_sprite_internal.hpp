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
            
            bool IsLoaded() const;
            void Draw    (const Sprite& sprite);

        private:
            std::string   texture{ "" };
            Pointer<Mesh> mesh   { nullptr };
            bool          loaded { false };
            uint          count  { 0 };
    };

    class SpriteRenderer
    {
        public:
            void QueueSprite(const std::string& sheet_id, const uint layer, const Sprite& sprite);
            void DrawLayer  (const uint layer);

        private:
            std::unordered_map<std::string, std::vector<Sprite>> draw_queue[256];
    };
    
    extern void InitSprites    ();
    extern void CloseSprites   ();
    extern void DrawSpriteLayer(uint layer);
}

#endif // VIOLET_ENGINE_SPRITE_INTERNAL_HPP