#ifndef VIOLET_ENGINE_SPRITE_INTERNAL_HPP
#define VIOLET_ENGINE_SPRITE_INTERNAL_HPP

namespace Violet
{
    struct SpriteDraw {
        uint  frame;
        float x;
        float y;
        float x_scale;
        float y_scale;
        float angle;
    };

    class SpriteSheet
    {
        public:
            SpriteSheet(const std::string& id, const std::string& path, const std::string& texture);
            ~SpriteSheet();
            
            bool IsLoaded() const;
            void QueueDraw(const uint layer, const SpriteDraw& sprite);
            void DrawLayer(const uint layer);

        private:
            std::string             id        { "" };
            bool                    loaded    { false };

            std::string             texture   { "" };
            Pointer<Mesh>           mesh      { nullptr };
            uint                    count     { 0 };
            std::vector<SpriteDraw> draw_queue[256];
    };

    extern void DrawSpriteLayer(uint layer);
}

#endif // VIOLET_ENGINE_SPRITE_INTERNAL_HPP