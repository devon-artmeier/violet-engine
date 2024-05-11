#ifndef VIOLET_ENGINE_TEXT_HPP
#define VIOLET_ENGINE_TEXT_HPP

namespace Violet
{
    extern void LoadFont       (const std::string& id, const std::string& path);
    extern void DestroyFont    (const std::string& id);
    extern void DestroyAllFonts();
	extern void DrawText       (const std::string& font_id, const uint size, const std::string& text, const uint layer,
                                const Vector2& pos, const Vector4& color);
}

#endif // VIOLET_ENGINE_TEXT_HPP