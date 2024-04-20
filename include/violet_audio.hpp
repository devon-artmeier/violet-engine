#ifndef VIOLET_ENGINE_AUDIO_HPP
#define VIOLET_ENGINE_AUDIO_HPP

#include <string>

namespace Violet
{
    extern void OpenSound(const std::string& id, const std::string& path);
    extern void CloseSound(const std::string& id);
    extern void PlaySound(const std::string& id);
    extern void LoopSound(const std::string& id, int loop_count = 0);
}

#endif // VIOLET_ENGINE_AUDIO_HPP