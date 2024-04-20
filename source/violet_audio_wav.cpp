#include "violet_engine.hpp"
#include "violet_audio_internal.hpp"
#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>

namespace Violet
{
    class WavSound: public Sound
    {
        public:
            WavSound(const std::string& id, const std::string& path)
            {
                this->id = id;
                if (drwav_init_file(&file, path.c_str(), nullptr) != 0) {
                    if (file.channels != 2 || file.sampleRate != 44100) {
                        drwav_uninit(&file);
                    } else {
                        open = true;
                    }
                }
            }

            ~WavSound()
            {
                if (open) {
                    drwav_uninit(&file);
                }
            }

            void Seek(const unsigned int sample)
            {
                drwav_seek_to_pcm_frame(&file, sample);
            }

            int Read(short* read_buffer, const size_t length)
            {
                return drwav_read_pcm_frames_s16(&file, length, read_buffer);
            }

        private:
            drwav file{ { 0 } };
    };

    Sound* OpenWavSound(const std::string& id, const std::string& path)
    {
        return new WavSound(id, path);
    }
}