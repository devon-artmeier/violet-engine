#ifndef VIOLET_ENGINE_AUDIO_INTERNAL_HPP
#define VIOLET_ENGINE_AUDIO_INTERNAL_HPP

#include "violet_audio.hpp"
#include "violet_types.hpp"

namespace Violet
{
    class Sound
    {
        public:
            Sound::Sound(const std::string& id);
            virtual Sound::~Sound();

            bool IsLoaded () const;
            bool IsPlaying() const;
            void Play     (const uint play_count);
            void Stop     ();
            int  GetVolume() const;
            void SetVolume(const int volume);
            void Render   (short* stream, short* read_buffer, const size_t length);

        protected:
            virtual void Seek(const uint sample) = 0;
            virtual int  Read(short* read_buffer, const size_t length) = 0;

            std::string  id           { "" };
            bool         loaded       { false };
            bool         playing      { false };
            uint         play_position{ 0 };
            uint         play_count   { 0 };
            uint         loop_start   { 0 };
            uint         loop_end     { 0 };
            int          volume       { 100 };
    };

    class SoundManager
    {
        public:
            SoundManager::~SoundManager();

            void   Render          (short* stream, short* read_buffer, const size_t length) const;
            Sound* GetSound        (const std::string& id) const;
            void   AddSound        (const std::string& id, Sound* sound);
            void   DestroySound    (const std::string& id);
            void   DestroyAllSounds();

        private:
            std::unordered_map<std::string, Sound*> sounds;
    };
    
    extern void   InitAudio    ();
    extern void   CloseAudio   ();
    extern Sound* LoadWavSound (const std::string& id, const std::string& path);
    extern Sound* LoadMp3Sound (const std::string& id, const std::string& path);
    extern Sound* LoadOggSound (const std::string& id, const std::string& path);
    extern Sound* LoadFlacSound(const std::string& id, const std::string& path);
}

#endif // VIOLET_ENGINE_AUDIO_INTERNAL_HPP