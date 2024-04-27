#include "violet_engine_internal.hpp"

#define DR_FLAC_IMPLEMENTATION
#include <dr_flac.h>

namespace Violet
{
    static void FlacMetadataHandler(void* user_data, drflac_metadata* metadata);

    class FlacSound: public Sound
    {
        public:
            FlacSound(const std::string& id, const std::string& path) : Sound(id)
            {
                this->file = drflac_open_file_with_metadata(path.c_str(), FlacMetadataHandler, this, nullptr);
                if (this->file != nullptr) {
                    if (this->file->channels != 2 || this->file->sampleRate != 44100) {
                        drflac_close(file);
                    } else {
                        this->length   = this->file->totalPCMFrameCount;
                        this->loop_end = this->length;
                        this->loaded   = true;
                    }
                }
            }

            ~FlacSound()
            {
                if (this->file != nullptr) {
                    drflac_close(this->file);
                }
            }

            void Seek(const ulonglong sample)
            {
                drflac_seek_to_pcm_frame(this->file, sample);
            }

            int Read(const Pointer<short>& read_buffer, const size_t length)
            {
                return drflac_read_pcm_frames_s16(this->file, length, read_buffer.Raw());
            }

            void CheckComment(const std::string& comment)
            {
                size_t equals = comment.find('=');

                if (equals != std::string::npos) {
                    std::string name = comment.substr(0, equals);
                    std::string value = comment.substr(equals + 1);
                    for (char& c : name) c = std::toupper(c);

                    if (name.compare("LOOPSTART") == 0) {
                        try {
                            this->loop_start = std::stoi(value);
                        } catch (...) {
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

        private:
            drflac* file{ nullptr };
    };

    Pointer<Sound> LoadFlacSound(const std::string& id, const std::string& path)
    {
        return Pointer<Sound>(new FlacSound(id, path));
    }

    static void FlacMetadataHandler(void* user_data, drflac_metadata* metadata)
    {
        if (metadata->type == DRFLAC_METADATA_BLOCK_TYPE_VORBIS_COMMENT) {
            const uchar* data = reinterpret_cast<const uchar*>(metadata->data.vorbis_comment.pComments);

            for (int i = 0; i < metadata->data.vorbis_comment.commentCount; i++) {
                ulong length = *(data++);
                length |= *(data++) << 8;
                length |= *(data++) << 16;
                length |= *(data++) << 24;

                std::string comment = "";
                for (ulong i = 0; i < length; i++) {
                    comment += *(data++);
                }

                reinterpret_cast<FlacSound*>(user_data)->CheckComment(comment);
            }
        }
    }
}