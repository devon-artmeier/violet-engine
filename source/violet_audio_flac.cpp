#include "violet_engine.hpp"
#include "violet_audio_internal.hpp"
#define DR_FLAC_IMPLEMENTATION
#include <dr_flac.h>

namespace Violet
{
    class FlacSound: public Sound
    {
        public:
            FlacSound(const std::string& id, const std::string& path) : Sound(id)
            {
                this->file = drflac_open_file(path.c_str(), nullptr);
                if (this->file != nullptr) {
                    if (this->file->channels != 2 || this->file->sampleRate != 44100) {
                        drflac_close(file);
                    } else {
                        this->loaded = true;
                    }
                }
            }

            ~FlacSound()
            {
                if (this->loaded) {
                    drflac_close(this->file);
                }
            }

            void Seek(const unsigned int sample)
            {
                drflac_seek_to_pcm_frame(this->file, sample);
            }

            int Read(short* read_buffer, const size_t length)
            {
                return drflac_read_pcm_frames_s16(this->file, length, read_buffer);
            }

        private:
            drflac* file{ nullptr };
    };

    Sound* LoadFlacSound(const std::string& id, const std::string& path)
    {
        return new FlacSound(id, path);
    }
}