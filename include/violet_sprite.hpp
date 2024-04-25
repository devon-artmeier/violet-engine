#ifndef VIOLET_ENGINE_SPRITE_HPP
#define VIOLET_ENGINE_SPRITE_HPP

#include "violet_texture.hpp"

namespace Violet
{
    extern void LoadSpriteSheet   (const std::string& id, const std::string& path, const std::string& texture);
    extern void DestroySpriteSheet(const std::string& id);
    extern void DrawSprite        (const std::string& sheet_id, const uint layer, const uint frame, Point2D<float> position,
                                   const Point2D<float> scale = { 1, 1 }, const float angle = 0, const TextureFilter filter = TextureFilter::Bilinear);
}

#endif // VIOLET_ENGINE_SPRITE_HPP