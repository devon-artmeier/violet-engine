#ifndef VIOLET_ENGINE_AUDIO_HPP
#define VIOLET_ENGINE_AUDIO_HPP

namespace Violet
{
    extern void PlaySound      (const std::string& id, const uint play_count = 1);
    extern void StopSound      (const std::string& id);
    extern int  GetMasterVolume();
    extern void SetMasterVolume(const int volume);
}

#endif // VIOLET_ENGINE_AUDIO_HPP