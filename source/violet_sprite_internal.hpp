#ifndef VIOLET_ENGINE_SPRITE_INTERNAL_HPP
#define VIOLET_ENGINE_SPRITE_INTERNAL_HPP

namespace Violet
{
    struct SpriteDraw {
        uint    frame;
        Vector2 pos;
        float   angle;
        Vector2 scale;
    };

    class SpriteSheet
    {
        public:
            SpriteSheet(const std::string& id, const std::string& path, const std::string& texture);
            ~SpriteSheet();

            std::string             id        { "" };
            uint                    count     { 0 };
            std::string             texture   { "" };
            Pointer<Mesh>           mesh      { nullptr };
            std::vector<SpriteDraw> draw_queue[256];
    };

    extern void InitSpriteSheetGroup   ();
    extern void DestroySpriteSheetGroup();
    extern void DrawSpriteLayer        (uint layer);
}

#endif // VIOLET_ENGINE_SPRITE_INTERNAL_HPP