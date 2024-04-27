#include "violet_engine_internal.hpp"

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
                    stb_vorbis_comment comments = stb_vorbis_get_comment(this->file);
                    
                    for (int i = 0; i < comments.comment_list_length; i++) {
                        std::string comment = comments.comment_list[i];
                        size_t      equals  = comment.find('=');
                        
                        if (equals != std::string::npos) {
                            std::string name  = comment.substr(0, equals);
                            std::string value = comment.substr(equals + 1);
                            for (char& c : name) c = std::toupper(c);

                            if (name.compare("LOOPSTART") == 0) {
                                try {
                                    this->loop_start = std::stoi(value);
                                } catch(...) {
#ifdef VIOLET_DEBUG
                                    LogError(this->id + ": Invalid loop start point \"" + value + "\"");
#endif
                                }
                            } else if (name.compare("LOOPEND") == 0) {
                                try {
                                    this->loop_end = std::stoi(value);
                                } catch (...) {
#ifdef VIOLET_DEBUG
                                    LogError(this->id + ": Invalid loop end point \"" + value + "\"");
#endif
                                }
                            }
                        }
                    }

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