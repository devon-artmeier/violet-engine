#ifndef VIOLET_ENGINE_AUDIO_HPP
#define VIOLET_ENGINE_AUDIO_HPP

namespace Violet
{
    extern void PlaySound      (const std::string& id, const uint loop_count);
    extern void StopSound      (const std::string& id);
    extern int  GetMasterVolume();
    extern void SetMasterVolume(const int volume);
}

#endif // VIOLET_ENGINE_AUDIO_HPP