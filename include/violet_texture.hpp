#ifndef VIOLET_ENGINE_TEXTURE_HPP
#define VIOLET_ENGINE_TEXTURE_HPP

#include "violet_types.hpp"

namespace Violet
{
    extern void LoadTexture   (const std::string& id, const std::string& path);
    extern void DestroyTexture(const std::string& id);
}

#endif // VIOLET_ENGINE_TEXTURE_HPP