#ifndef VIOLET_ENGINE_SPRITE_HPP
#define VIOLET_ENGINE_SPRITE_HPP

namespace Violet
{
    extern void DrawSprite(const std::string& sheet_id, const uint layer, const uint frame, const float x, const float y,
                           const float x_scale = 1.0f, const float y_scale = 1.0f, const float angle = 0.0f);
}

#endif // VIOLET_ENGINE_SPRITE_HPP