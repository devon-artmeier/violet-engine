#ifndef VIOLET_ENGINE_AUDIO_INTERNAL_HPP
#define VIOLET_ENGINE_AUDIO_INTERNAL_HPP

namespace Violet
{
    class Sound
    {
        public:
            Sound(const std::string& id);
            virtual ~Sound();

            bool IsLoaded () const;
            bool IsPlaying() const;
            void Play     (const uint play_count);
            void Stop     ();
            int  GetVolume() const;
            void SetVolume(const int volume);
            void Render   (Pointer<short> stream, Pointer<short> read_buffer, const size_t length);

        protected:
            virtual void Seek(const uint sample) = 0;
            virtual int  Read(const Pointer<short>& read_buffer, const size_t length) = 0;

            std::string id           { "" };
            bool        loaded       { false };
            bool        playing      { false };
            uint        play_position{ 0 };
            uint        play_count   { 0 };
            uint        loop_start   { 0 };
            uint        loop_end     { 0 };
            int         volume       { 100 };
    };
    
    extern void           InitAudio    ();
    extern void           CloseAudio   ();
    extern Pointer<Sound> LoadWavSound (const std::string& id, const std::string& path);
    extern Pointer<Sound> LoadMp3Sound (const std::string& id, const std::string& path);
    extern Pointer<Sound> LoadOggSound (const std::string& id, const std::string& path);
    extern Pointer<Sound> LoadFlacSound(const std::string& id, const std::string& path);
}

#endif // VIOLET_ENGINE_AUDIO_INTERNAL_HPP