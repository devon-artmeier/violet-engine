#ifndef VIOLET_ENGINE_SPRITE_HPP
#define VIOLET_ENGINE_SPRITE_HPP

#include "violet_types.hpp"

namespace Violet
{
    struct Sprite {
        uint  frame;
        float x;
        float y;
        float x_scale;
        float y_scale;
        float angle;
    };

    extern void LoadSpriteSheet   (const std::string& id, const std::string& path, const std::string& texture);
    extern void DestroySpriteSheet(const std::string& id);
    extern void DrawSprite        (const std::string& sheet_id, const uint frame, const Sprite& sprite);
}

#endif // VIOLET_ENGINE_SPRITE_HPP