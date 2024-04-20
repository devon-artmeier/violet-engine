#include "violet_engine.hpp"
#include "violet_audio_internal.hpp"
#include <stb_vorbis.c>

namespace Violet
{
    class OggSound: public Sound
    {
        public:
            OggSound(const std::string& path)
            {
                file = stb_vorbis_open_filename(path.c_str(), nullptr, nullptr);
            }

            ~OggSound()
            {
                stb_vorbis_close(file);
            }

            bool IsOpened()
            {
                return file != nullptr;
            }

            void Render(short* stream, short* read_buffer, const size_t length)
            {
                size_t  read_count      = 0;
                size_t  samples_left    = length;
                short*  read_buffer_pos = read_buffer;
                bool    looped          = false;

                while (read_count < length) {
                    int samples_read    = stb_vorbis_get_samples_short_interleaved(file, 2, read_buffer_pos, samples_left * 2);
                    read_count          += samples_read;
                    samples_left        -= samples_read;
                    read_buffer_pos     += samples_read * 2;

                    if (samples_read == 0) {
                        if (looped || loop_count == 0) {
                            break;
                        } else {
                            if (loop_count > 0) {
                                loop_count--;
                            }
                            looped = true;
                        }
                    } else {
                        looped = false;
                    }

                    if (looped) {
                        stb_vorbis_seek(file, 0);
                    }
                }

                for (int i = 0; i < length; i++) {
                    *(stream++) += *(read_buffer++);
                    *(stream++) += *(read_buffer++);
                }
            }

        private:
            stb_vorbis* file{ nullptr };
    };

    Sound* OpenVorbisSound(const std::string& path)
    {
        return new OggSound(path);
    }
}