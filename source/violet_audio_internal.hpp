#ifndef VIOLET_ENGINE_AUDIO_INTERNAL_HPP
#define VIOLET_ENGINE_AUDIO_INTERNAL_HPP

#include <miniaudio.h>
#ifdef PlaySound
#undef PlaySound
#endif

namespace Violet
{
    class Sound
    {
        public:
            Sound(const std::string& id, const std::string& path);
            ~Sound();

            bool      IsLoaded    () const;
            bool      IsPlaying   () const;
            void      Play        (const bool loop);
            void      Stop        ();
            float     GetVolume   () const;
            void      SetVolume   (const float volume);
            ulonglong GetLength   ();
            ulonglong GetLoopStart();
            ulonglong GetLoopEnd  ();
            void      SetLoopStart(const ulonglong point);
            void      SetLoopEnd  (const ulonglong point);
            void      SetLoop     (const ulonglong start, const ulonglong end);

        private:
            std::string id    { "" };
            bool        loaded{ false };
            ma_sound    sound { { 0 } };
            ulonglong   length{ 0};
    };

    class AudioPlayer
    {
        public:
            AudioPlayer();
            ~AudioPlayer();

            bool InitSound(const std::string& path, ma_sound* sound);
            void Callback (Pointer<ma_uint8> buffer, ma_uint64 length);

        private:
            ma_engine        engine{ { 0 } };
            SDL_AudioStream* stream{ nullptr };
    };
    
    extern void InitAudio ();
    extern void CloseAudio();
}

#endif // VIOLET_ENGINE_AUDIO_INTERNAL_HPP