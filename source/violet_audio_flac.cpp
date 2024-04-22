#include "violet_audio_internal.hpp"
#include "violet_message_internal.hpp"
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
#ifdef VIOLET_DEBUG
                        LogInfo("Loaded FLAC sound \"" + id + "\" from \"" + path + "\"");
#endif
                    }
                }
            }

            ~FlacSound()
            {
                if (this->file != nullptr) {
                    drflac_close(this->file);
                }
            }

            void Seek(const uint sample)
            {
                drflac_seek_to_pcm_frame(this->file, sample);
            }

            int Read(Pointer<short> read_buffer, const size_t length)
            {
                return drflac_read_pcm_frames_s16(this->file, length, read_buffer.Raw());
            }

        private:
            drflac* file{ nullptr };
    };

    Pointer<Sound> LoadFlacSound(const std::string& id, const std::string& path)
    {
        return Pointer<Sound>(new FlacSound(id, path));
    }
}