#ifndef VIOLET_ENGINE_AUDIO_INTERNAL_HPP
#define VIOLET_ENGINE_AUDIO_INTERNAL_HPP

#include "violet_audio.hpp"
#include "violet_resource.hpp"

namespace Violet
{
    class Sound : public Resource
    {
        public:
            Sound(const std::string& id) : Resource(id) { }
            virtual ~Sound();

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

            bool         loaded       { false };
            bool         playing      { false };
            uint         play_position{ 0 };
            uint         play_count   { 0 };
            uint         loop_start   { 0 };
            uint         loop_end     { 0 };
            int          volume       { 100 };
    };
    
    class SoundGroup : public ResourceGroup
    {
        public:
            void Render(short* stream, short* read_buffer, const size_t length) const;
    };
    
    extern void   InitAudio    ();
    extern void   CloseAudio   ();
    extern Sound* LoadWavSound (const std::string& id, const std::string& path);
    extern Sound* LoadMp3Sound (const std::string& id, const std::string& path);
    extern Sound* LoadOggSound (const std::string& id, const std::string& path);
    extern Sound* LoadFlacSound(const std::string& id, const std::string& path);
}

#endif // VIOLET_ENGINE_AUDIO_INTERNAL_HPP