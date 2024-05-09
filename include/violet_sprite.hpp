#ifndef VIOLET_ENGINE_SPRITE_HPP
#define VIOLET_ENGINE_SPRITE_HPP

namespace Violet
{
    extern void LoadSpriteSheet       (const std::string& id, const std::string& path, const std::string& texture);
    extern void DestroySpriteSheet    (const std::string& id);
    extern void DestroyAllSpriteSheets();
    extern void DrawSprite            (const std::string& sprite_sheet_id, const uint layer, const uint frame, const Vector2& pos,
                                       const float angle = 0.0f, const Vector2& scale = Vector2(1.0f));
}

#endif // VIOLET_ENGINE_SPRITE_HPP