#ifndef VIOLET_ENGINE_TEXTURE_HPP
#define VIOLET_ENGINE_TEXTURE_HPP

#include "violet_types.hpp"

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

    extern void LoadTexture   (const std::string& id, const std::string& path);
    extern void DestroyTexture(const std::string& id);
}

#endif // VIOLET_ENGINE_TEXTURE_HPP