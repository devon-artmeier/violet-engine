#ifndef VIOLET_ENGINE_AUDIO_HPP
#define VIOLET_ENGINE_AUDIO_HPP

namespace Violet
{
    extern void      PlaySound        (const std::string& id);
    extern void      LoopSound        (const std::string& id);
    extern void      StopSound        (const std::string& id);
    extern bool      IsSoundPlaying   (const std::string& id);
    extern bool      IsSoundLooping   (const std::string& id);
    extern bool      IsSoundAtEnd     (const std::string& id);
    extern float     GetSoundVolume   (const std::string& id);
    extern void      SetSoundVolume   (const std::string& id, const float volume);
    extern float     GetSoundPanning  (const std::string& id);
    extern void      SetSoundPanning  (const std::string& id, const float panning);
    extern ulonglong GetSoundLength   (const std::string& id);
    extern ulonglong GetSoundLoopStart(const std::string& id);
    extern ulonglong GetSoundLoopEnd  (const std::string& id);
    extern void      SetSoundLoopStart(const std::string& id, const ulonglong point);
    extern void      SetSoundLoopEnd  (const std::string& id, const ulonglong point);
    extern void      SetSoundLoop     (const std::string& id, const ulonglong start, const ulonglong end);
    extern float     GetMasterVolume  ();
    extern void      SetMasterVolume  (const float volume);
}

#endif // VIOLET_ENGINE_AUDIO_HPP