#ifndef VIOLET_ENGINE_SPRITE_INTERNAL_HPP
#define VIOLET_ENGINE_SPRITE_INTERNAL_HPP

#include "violet_mesh_internal.hpp"
#include "violet_resource.hpp"
#include "violet_sprite.hpp"

namespace Violet
{
    struct SpriteDraw {
        uint           frame;
        Point2D<float> position;
        Point2D<float> scale;
        float          angle;
        TextureFilter  filter;
    };

    class SpriteSheet : public Resource
    {
        public:
            SpriteSheet(const std::string& id, const std::string& path, const std::string& texture);
            
            void QueueDraw(const uint layer, const SpriteDraw& sprite);
            void DrawLayer(const uint layer);

        private:
            std::string             texture   { "" };
            Pointer<Mesh>           mesh      { nullptr };
            uint                    count     { 0 };
            std::vector<SpriteDraw> draw_queue[256];
    };

    class SpriteSheetGroup : public ResourceGroup<SpriteSheet>
    {
        public:
            void DrawLayer(const uint layer);
    };
    
    extern void InitSprites    ();
    extern void CloseSprites   ();
    extern void DrawSpriteLayer(uint layer);
}

#endif // VIOLET_ENGINE_SPRITE_INTERNAL_HPP