#ifndef VIOLET_ENGINE_AUDIO_INTERNAL_HPP
#define VIOLET_ENGINE_AUDIO_INTERNAL_HPP

#include <string>
#include <unordered_map>

namespace Violet
{
    class Sound
    {
        public:
            virtual         Sound::~Sound() { }

            bool            IsOpen();
            bool            IsPlaying();
            void            Play(const unsigned int play_count);
            void            Stop();
            void            Render(short* stream, short* read_buffer, const size_t length);

        protected:
            virtual void    Seek(const unsigned int sample) = 0;
            virtual int     Read(short* read_buffer, const size_t length) = 0;

            bool            open{ false };
            bool            playing{ false };
            unsigned int    play_position{ 0 };
            unsigned int    play_count{ 0 };
            unsigned int    loop_start{ 0 };
            unsigned int    loop_end{ 0 };
    };

    class SoundManager
    {
        public:
            SoundManager::~SoundManager();

            void    Render(short* stream, short* read_buffer, const size_t length);
            Sound*  GetSound(const std::string& id);
            void    AddSound(const std::string& id, Sound* sound);
            void    CloseSound(const std::string& id);
            void    CloseAllSounds();

        private:
            std::unordered_map<std::string, Sound*> sounds;
    };
    
    extern void     InitAudio();
    extern void     CloseAudio();
    extern Sound*   OpenVorbisSound(const std::string& path);
}

#endif // VIOLET_ENGINE_AUDIO_INTERNAL_HPP