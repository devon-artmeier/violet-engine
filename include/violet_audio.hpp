#ifndef VIOLET_ENGINE_AUDIO_HPP
#define VIOLET_ENGINE_AUDIO_HPP

namespace Violet
{
    extern void      PlaySound         (const std::string& id, const bool loop = false);
    extern void      StopSound         (const std::string& id);
    extern int       GetSoundVolume    (const std::string& id);
    extern void      SetSoundVolume    (const std::string& id, const int volume);
    extern ulonglong GetSoundLength    (const std::string& id);
    extern ulonglong GetSoundLoopStart (const std::string& id);
    extern ulonglong GetSoundLoopEnd   (const std::string& id);
    extern void      SetSoundLoopStart (const std::string& id, const ulonglong point);
    extern void      SetSoundLoopEnd   (const std::string& id, const ulonglong point);
    extern void      SetSoundLoop      (const std::string& id, const ulonglong start, const ulonglong end);
}

#endif // VIOLET_ENGINE_AUDIO_HPP