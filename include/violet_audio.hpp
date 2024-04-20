#ifndef VIOLET_ENGINE_AUDIO_HPP
#define VIOLET_ENGINE_AUDIO_HPP

#include <string>

namespace Violet
{
    extern void OpenSound(const std::string& id, const std::string& path);
    extern void CloseSound(const std::string& id);
    extern void PlaySound(const std::string& id, const unsigned int loop_count);
    extern void StopSound(const std::string& id);
    extern int  GetMasterVolume();
    extern void SetMasterVolume(const int volume);
}

#endif // VIOLET_ENGINE_AUDIO_HPP