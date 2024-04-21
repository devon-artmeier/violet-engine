#ifndef VIOLET_ENGINE_AUDIO_HPP
#define VIOLET_ENGINE_AUDIO_HPP

#include "violet_types.hpp"

namespace Violet
{
    extern void LoadSound      (const std::string& id, const std::string& path);
    extern void DestroySound   (const std::string& id);
    extern void PlaySound      (const std::string& id, const uint loop_count);
    extern void StopSound      (const std::string& id);
    extern int  GetMasterVolume();
    extern void SetMasterVolume(const int volume);
}

#endif // VIOLET_ENGINE_AUDIO_HPP