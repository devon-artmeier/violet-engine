#ifndef VIOLET_ENGINE_TEXTURE_HPP
#define VIOLET_ENGINE_TEXTURE_HPP

namespace Violet
{
    enum class TextureFilter {
        Bilinear,
        Nearest
    };

    enum class TextureWrap {
        Repeat,
        Mirror,
        ClampEdge,
        ClampBorder
    };

    extern int           GetTextureWidth (const std::string& id);
    extern int           GetTextureHeight(const std::string& id);
    extern TextureFilter GetTextureFilter(const std::string& id);
    extern void          SetTextureFilter(const std::string& id, const TextureFilter filter);
    extern TextureWrap   GetTextureWrapX (const std::string& id);
    extern TextureWrap   GetTextureWrapY (const std::string& id);
    extern void          SetTextureWrapX (const std::string& id, const TextureWrap wrap);
    extern void          SetTextureWrapY (const std::string& id, const TextureWrap wrap);
}

#endif // VIOLET_ENGINE_TEXTURE_HPP