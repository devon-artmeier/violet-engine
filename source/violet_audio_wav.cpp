#include "violet_audio_internal.hpp"
#include "violet_message_internal.hpp"
#include "violet_types.hpp"
#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>

namespace Violet
{
    class WavSound: public Sound
    {
        public:
            WavSound(const std::string& id, const std::string& path) : Sound(id)
            {
                if (drwav_init_file(&this->file, path.c_str(), nullptr) != 0) {
                    if (this->file.channels != 2 || this->file.sampleRate != 44100) {
                        drwav_uninit(&this->file);
                    } else {
                        this->loaded = true;
#ifdef VIOLET_DEBUG
                        LogInfo("Loaded WAV sound \"" + id + "\" from \"" + path + "\"");
#endif
                    }
                }
            }

            ~WavSound()
            {
                if (this->loaded) {
                    drwav_uninit(&this->file);
                }
            }

            void Seek(const uint sample)
            {
                drwav_seek_to_pcm_frame(&this->file, sample);
            }

            int Read(short* read_buffer, const size_t length)
            {
                return drwav_read_pcm_frames_s16(&this->file, length, read_buffer);
            }

        private:
            drwav file{ { 0 } };
    };

    Sound* LoadWavSound(const std::string& id, const std::string& path)
    {
        return new WavSound(id, path);
    }
}