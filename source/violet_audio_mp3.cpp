#include "violet_engine.hpp"
#include "violet_audio_internal.hpp"
#define DR_MP3_IMPLEMENTATION
#include <dr_mp3.h>

namespace Violet
{
    class Mp3Sound: public Sound
    {
        public:
            Mp3Sound(const std::string& id, const std::string& path)
            {
                this->id = id;
                if (drmp3_init_file(&file, path.c_str(), nullptr) != 0) {
                    if (file.channels != 2 || file.sampleRate != 44100) {
                        drmp3_uninit(&file);
                    } else {
                        open = true;
                    }
                }
            }

            ~Mp3Sound()
            {
                if (open) {
                    drmp3_uninit(&file);
                }
            }

            void Seek(const unsigned int sample)
            {
                drmp3_seek_to_pcm_frame(&file, sample);
            }

            int Read(short* read_buffer, const size_t length)
            {
                return drmp3_read_pcm_frames_s16(&file, length, read_buffer);
            }

        private:
            drmp3 file{ { 0 } };
    };

    Sound* OpenMp3Sound(const std::string& id, const std::string& path)
    {
        return new Mp3Sound(id, path);
    }
}