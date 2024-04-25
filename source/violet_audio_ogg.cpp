#include "violet_audio_internal.hpp"
#include "violet_message_internal.hpp"
#include <stb_vorbis.c>

namespace Violet
{
    class OggSound: public Sound
    {
        public:
            OggSound(const std::string& id, const std::string& path) : Sound(id)
            {
                this->file = stb_vorbis_open_filename(path.c_str(), nullptr, nullptr);
                if (this->file != nullptr) {
                    this->loaded = true;
                }
            }

            ~OggSound()
            {
                if (this->file != nullptr) {
                    stb_vorbis_close(this->file);
                }
            }

            void Seek(const uint sample)
            {
                stb_vorbis_seek(this->file, sample);
            }

            int Read(const Pointer<short>& read_buffer, const size_t length)
            {
                return stb_vorbis_get_samples_short_interleaved(this->file, 2, read_buffer.Raw(), length * 2);
            }

        private:
            stb_vorbis* file{ nullptr };
    };

    Pointer<Sound> LoadOggSound(const std::string& id, const std::string& path)
    {
        return Pointer<Sound>(new OggSound(id, path));
    }
}