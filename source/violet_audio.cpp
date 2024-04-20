#include <SDL3/SDL.h>
#include "violet_engine.hpp"
#include "violet_audio_internal.hpp"

namespace Violet
{
    static SDL_AudioStream* audio_stream{ nullptr };
    static SoundManager*    sound_manager{ nullptr };

    static void AudioCallback(void *user_data, SDL_AudioStream *stream, int additional_amount, int total_amount)
    {
        if (additional_amount > 0) {
            Uint8 *stream_data = SDL_stack_alloc(Uint8, additional_amount);
            Uint8 *read_buffer = SDL_stack_alloc(Uint8, additional_amount);

            if (stream_data != nullptr && read_buffer != nullptr) {
                memset(stream_data, 0, additional_amount);

                sound_manager->Render(reinterpret_cast<short*>(stream_data),
                                      reinterpret_cast<short*>(read_buffer),
                                      additional_amount);

                SDL_PutAudioStreamData(stream, stream_data, additional_amount);
            }
            
            if (stream_data != nullptr) SDL_stack_free(stream_data);
            if (read_buffer != nullptr) SDL_stack_free(read_buffer);
        }
    }

    void InitAudio()
    {
        SDL_AudioSpec audio_spec = { 0 };
        audio_spec.freq     = 44100;
        audio_spec.format   = SDL_AUDIO_S16;
        audio_spec.channels = 2;

        audio_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_OUTPUT, &audio_spec, AudioCallback, nullptr);
        if (audio_stream == nullptr) {
            MessageBoxError("Failed to open audio device stream.");
        } else {
            SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(audio_stream));
        }

        sound_manager = new SoundManager();
    }

    void CloseAudio()
    {
        delete sound_manager;

        if (audio_stream != nullptr) {
            SDL_PauseAudioDevice(SDL_GetAudioStreamDevice(audio_stream));
            SDL_CloseAudioDevice(SDL_GetAudioStreamDevice(audio_stream));
        }
    }

    void OpenSound(const std::string& id, const std::string& path)
    {
        sound_manager->AddSound(id, OpenVorbisSound(path));
    }

    void CloseSound(const std::string& id)
    {
        sound_manager->CloseSound(id);
    }

    void PlaySound(const std::string& id, const unsigned int play_count)
    {
        Sound* sound = sound_manager->GetSound(id);
        if (sound != nullptr) {
            sound->Play(play_count);
        }
    }

    bool Sound::IsOpen()
    {
       return open;
    }

    bool Sound::IsPlaying()
    {
        return playing;
    }

    void Sound::Play(const unsigned int play_count)
    {
        if (IsOpen()) {
            this->play_count = play_count;
            play_position = 0;
            Seek(0);
            playing = true;
        }
    }

    void Sound::Stop()
    {
        playing = false;
        play_position = 0;
        play_count = 0;
    }

    void Sound::Render(short* stream, short* read_buffer, const size_t length)
    {
        if (open && playing) {
            size_t  read_count      = 0;
            short*  read_buffer_pos = read_buffer;
            bool    loop            = false;

            while (read_count < length) {
                size_t samples_to_read = length - read_count;
                if (play_count != 1 && loop_end != 0 && (loop_end - play_position) < samples_to_read) {
                    samples_to_read = loop_end - play_position;
                }

                int samples_read    = Read(read_buffer_pos, samples_to_read);
                play_position       += samples_read;
                read_count          += samples_read;
                read_buffer_pos     += samples_read * 2;

                if (samples_read == 0) {
                    if (loop) break;
                    loop = true;
                } else {
                    loop = (loop_end != 0 && play_position >= loop_end);
                }

                if (loop) {
                    if (play_count == 1) break;
                    if (play_count > 1) {
                        play_count--;
                    }
                    play_position = loop_start;
                    Seek(loop_start);
                }
            }

            for (int i = 0; i < length; i++) {
                *(stream++) += *(read_buffer++);
                *(stream++) += *(read_buffer++);
            }
        }
    }

    SoundManager::~SoundManager()
    {
        CloseAllSounds();
    }

    void SoundManager::Render(short* stream, short* read_buffer, const size_t length)
    {
        for (auto sound_entry : sounds) {
            memset(read_buffer, 0, length);
            sound_entry.second->Render(stream, read_buffer, length / (sizeof(short) * 2));
        }
    }

    Sound* SoundManager::GetSound(const std::string& id)
    {
        auto sound = sounds.find(id);
        if (sound != sounds.end()) {
            return sound->second;
        }
        return nullptr;
    }

    void SoundManager::AddSound(const std::string& id, Sound* sound)
    {
        CloseSound(id);
        sounds.insert({id, sound});
    }

    void SoundManager::CloseSound(const std::string& id)
    {
        Sound* sound = GetSound(id);
        if (sound != nullptr) {
            delete sound;
            sounds.erase(id);
        }
    }

    void SoundManager::CloseAllSounds()
    {
        for (auto sound : sounds) {
            delete sound.second;
        }
        sounds.clear();
    }
}