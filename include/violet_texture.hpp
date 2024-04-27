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
}

#endif // VIOLET_ENGINE_TEXTURE_HPP