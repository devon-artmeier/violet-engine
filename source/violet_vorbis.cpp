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
                open = file != nullptr;
            }

            ~OggSound()
            {
                stb_vorbis_close(file);
            }

            void Seek(const unsigned int sample)
            {
                stb_vorbis_seek(file, sample);
            }

            int Read(short* read_buffer, const size_t length)
            {
                return stb_vorbis_get_samples_short_interleaved(file, 2, read_buffer, length * 2);
            }

        private:
            stb_vorbis* file{ nullptr };
    };

    Sound* OpenVorbisSound(const std::string& path)
    {
        return new OggSound(path);
    }
}