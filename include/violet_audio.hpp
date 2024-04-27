#ifndef VIOLET_ENGINE_AUDIO_HPP
#define VIOLET_ENGINE_AUDIO_HPP

namespace Violet
{
    extern void      PlaySound        (const std::string& id, const uint play_count = 1);
    extern void      StopSound        (const std::string& id);
    extern int       GetSoundVolume   (const std::string& id);
    extern void      SetSoundVolume   (const std::string& id, const int volume);
    extern ulonglong GetSoundLength   (const std::string& id);
    extern ulonglong GetSoundLoopStart(const std::string& id);
    extern ulonglong GetSoundLoopEnd  (const std::string& id);
    extern void      SetSoundLoopStart(const std::string& id, const ulonglong point);
    extern void      SetSoundLoopEnd  (const std::string& id, const ulonglong point);
    extern int       GetMasterVolume  ();
    extern void      SetMasterVolume  (const int volume);
}

#endif // VIOLET_ENGINE_AUDIO_HPP