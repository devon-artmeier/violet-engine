#include "violet_engine.hpp"
#include "violet_audio_internal.hpp"
#define DR_FLAC_IMPLEMENTATION
#include <dr_flac.h>

namespace Violet
{
    class FlacSound: public Sound
    {
        public:
            FlacSound(const std::string& id, const std::string& path)
            {
                this->id = id;
                file = drflac_open_file(path.c_str(), nullptr);
                if (file != nullptr) {
                    if (file->channels != 2 || file->sampleRate != 44100) {
                        drflac_close(file);
                    } else {
                        open = true;
                    }
                }
            }

            ~FlacSound()
            {
                if (open) {
                    drflac_close(file);
                }
            }

            void Seek(const unsigned int sample)
            {
                drflac_seek_to_pcm_frame(file, sample);
            }

            int Read(short* read_buffer, const size_t length)
            {
                return drflac_read_pcm_frames_s16(file, length, read_buffer);
            }

        private:
            drflac* file{ nullptr };
    };

    Sound* OpenFlacSound(const std::string& id, const std::string& path)
    {
        return new FlacSound(id, path);
    }
}