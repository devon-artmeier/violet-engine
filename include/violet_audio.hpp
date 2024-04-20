#ifndef VIOLET_ENGINE_AUDIO_HPP
#define VIOLET_ENGINE_AUDIO_HPP

#include <string>

namespace Violet
{
    extern void OpenSound(const std::string& id, const std::string& path);
    extern void CloseSound(const std::string& id);
    extern void PlaySound(const std::string& id, const unsigned int loop_count);
}

#endif // VIOLET_ENGINE_AUDIO_HPP