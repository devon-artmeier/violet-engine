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

            bool            IsPlaying();
            void            Play(const int loop_count);
            bool            IsLooping();
            void            StepLoopCount();
            void            Stop();

            virtual bool    IsOpened() = 0;
            virtual void    Restart() = 0;
            virtual void    Seek(int sample) = 0;
            virtual int     ReadSamples(short* read_buffer, const size_t length) = 0;

        protected:
            bool            playing{ false };
            int             loop_count{ 0 };
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