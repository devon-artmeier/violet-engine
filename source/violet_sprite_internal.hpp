#ifndef VIOLET_ENGINE_SPRITE_INTERNAL_HPP
#define VIOLET_ENGINE_SPRITE_INTERNAL_HPP

namespace Violet
{
    struct SpriteDraw {
        uint     frame;
        Vector2D pos;
        float    angle;
        Vector2D scale;
    };

    class SpriteSheet
    {
        public:
            SpriteSheet(const std::string& id, const std::string& path, const std::string& texture);
            ~SpriteSheet();
            
            bool IsLoaded() const;
            void QueueDraw(const uint layer, const SpriteDraw& draw);
            void DrawLayer(const uint layer);

        private:
            std::string             id        { "" };
            bool                    loaded    { false };
            uint                    count{ 0 };
            std::string             texture   { "" };
            Pointer<Mesh>           mesh      { nullptr };
            std::vector<SpriteDraw> draw_queue[256];
    };

    extern void InitSprites();
    extern void CloseSprites();
    extern void DrawSpriteLayer(uint layer);
}

#endif // VIOLET_ENGINE_SPRITE_INTERNAL_HPP