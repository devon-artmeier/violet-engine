#ifndef VIOLET_ENGINE_AUDIO_INTERNAL_HPP
#define VIOLET_ENGINE_AUDIO_INTERNAL_HPP

#define MA_NO_DEVICE_IO
#define MA_NO_RUNTIME_LINKING
#ifdef VIOLET_DEBUG
#define MA_DEBUG_OUTPUT
#endif
#include <miniaudio.h>
#ifdef PlaySound
#undef PlaySound
#endif
#ifdef DrawText
#undef DrawText
#endif
#ifdef near
#undef near
#endif
#ifdef far
#undef far
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
            bool      IsLooping   () const;
            bool      IsAtEnd     () const;
            void      Play        (const bool loop);
            void      Stop        ();
            float     GetVolume   () const;
            void      SetVolume   (const float volume);
            float     GetPanning  () const;
            void      SetPanning  (const float panning);
            float     GetPitch    () const;
            void      SetPitch    (const float pitch);
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

            bool  InitSound(const std::string& path, ma_sound* sound);
            void  Callback (Pointer<ma_uint8> buffer, ma_uint64 length);
            float GetVolume();
            void  SetVolume(const float volume);

        private:
            bool             initialized{ false };
            ma_engine        engine     { { 0 } };
            SDL_AudioStream* stream     { nullptr };
    };
    
    extern void InitAudio ();
    extern void CloseAudio();
}

#endif // VIOLET_ENGINE_AUDIO_INTERNAL_HPP