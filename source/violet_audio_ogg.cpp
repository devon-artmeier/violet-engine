#include "violet_engine.hpp"
#include "violet_audio_internal.hpp"
#include <stb_vorbis.c>

namespace Violet
{
    class OggSound: public Sound
    {
        public:
            OggSound(const std::string& id, const std::string& path) : Sound(id)
            {
                this->file   = stb_vorbis_open_filename(path.c_str(), nullptr, nullptr);
                if (this->file != nullptr) {
                    this->loaded = true;
#ifdef VIOLET_DEBUG
                    LogInfo("Loaded OGG sound \"" + id + "\" from \"" + path + "\"");
#endif
                }
            }

            ~OggSound()
            {
                if (this->loaded) {
                    stb_vorbis_close(this->file);
                }
            }

            void Seek(const unsigned int sample)
            {
                stb_vorbis_seek(this->file, sample);
            }

            int Read(short* read_buffer, const size_t length)
            {
                return stb_vorbis_get_samples_short_interleaved(this->file, 2, read_buffer, length * 2);
            }

        private:
            stb_vorbis* file{ nullptr };
    };

    Sound* LoadOggSound(const std::string& id, const std::string& path)
    {
        return new OggSound(id, path);
    }
}