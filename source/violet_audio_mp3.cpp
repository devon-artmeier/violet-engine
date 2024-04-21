#include "violet_engine.hpp"
#include "violet_audio_internal.hpp"
#define DR_MP3_IMPLEMENTATION
#include <dr_mp3.h>

namespace Violet
{
    class Mp3Sound: public Sound
    {
        public:
            Mp3Sound(const std::string& id, const std::string& path) : Sound(id)
            {
                if (drmp3_init_file(&this->file, path.c_str(), nullptr) != 0) {
                    if (this->file.channels != 2 || this->file.sampleRate != 44100) {
                        drmp3_uninit(&this->file);
                    } else {
                        this->loaded = true;
#ifdef VIOLET_DEBUG
                        LogInfo("Loaded MP3 sound \"" + id + "\" from \"" + path + "\"");
#endif
                    }
                }
            }

            ~Mp3Sound()
            {
                if (this->loaded) {
                    drmp3_uninit(&this->file);
                }
            }

            void Seek(const unsigned int sample)
            {
                drmp3_seek_to_pcm_frame(&this->file, sample);
            }

            int Read(short* read_buffer, const size_t length)
            {
                return drmp3_read_pcm_frames_s16(&this->file, length, read_buffer);
            }

        private:
            drmp3 file{ { 0 } };
    };

    Sound* LoadMp3Sound(const std::string& id, const std::string& path)
    {
        return new Mp3Sound(id, path);
    }
}