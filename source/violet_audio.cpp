#include <SDL3/SDL.h>
#include "violet_engine.hpp"
#include "violet_audio_internal.hpp"

namespace Violet
{
    static SDL_AudioStream* audio_stream{ nullptr };
    static SoundManager*    sound_manager{ nullptr };
    static int              master_volume{ 100 };

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
        if (audio_stream != nullptr) {
            SDL_PauseAudioDevice(SDL_GetAudioStreamDevice(audio_stream));
            SDL_CloseAudioDevice(SDL_GetAudioStreamDevice(audio_stream));
        }
        delete sound_manager;
    }

    void OpenSound(const std::string& id, const std::string& path)
    {
#ifdef VIOLET_DEBUG
        LogInfo("Loading sound \"" + path + "\" with ID \"" + id + "\"");
#endif

        Sound* sound = OpenWavSound(id, path);
        if (sound->IsOpen()) { sound_manager->AddSound(id, sound); return; }
        delete sound;

        sound = OpenMp3Sound(id, path);
        if (sound->IsOpen()) { sound_manager->AddSound(id, sound); return; }
        delete sound;

        sound = OpenOggSound(id, path);
        if (sound->IsOpen()) { sound_manager->AddSound(id, sound); return; }
        delete sound;

        sound = OpenFlacSound(id, path);
        if (sound->IsOpen()) { sound_manager->AddSound(id, sound); return; }
        delete sound;

#ifdef VIOLET_DEBUG
        LogError("Failed to load sound \"" + path + "\" with ID \"" + id + "\"");
#endif
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

    void StopSound(const std::string& id)
    {
        Sound* sound = sound_manager->GetSound(id);
        if (sound != nullptr) {
            sound->Stop();
        }
    }

    int GetMasterVolume()
    {
        return master_volume;
    }

    void SetMasterVolume(const int volume)
    {
        master_volume = (volume < 0) ? 0 : ((volume > 100) ? 100 : volume);
    }

    Sound::~Sound()
    {
#ifdef VIOLET_DEBUG
        if (open) {
            LogInfo("Closing sound \"" + id + "\"");
        }
#endif
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
        if (open) {
#ifdef VIOLET_DEBUG
            LogInfo("Playing sound \"" + id + "\" " + ((play_count == 0) ? "infinite" : std::to_string(play_count) + " time(s)"));
#endif
            this->play_count = play_count;
            play_position = 0;
            Seek(0);
            playing = true;
        }
    }

    void Sound::Stop()
    {
#ifdef VIOLET_DEBUG
        LogInfo("Stopping sound \"" + id + "\"");
#endif
        playing = false;
        play_position = 0;
        play_count = 0;
    }

    int Sound::GetVolume()
    {
        return volume;
    }

    void Sound::SetVolume(const int volume)
    {
        this->volume = (volume < 0) ? 0 : ((volume > 100) ? 100 : volume);
    }

    static inline int ApplyVolume(const int sample, const int volume)
    {
        return (sample * volume) / 100;
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

            for (int i = 0; i < length * 2; i++) {
                int sample = ApplyVolume(ApplyVolume(*(read_buffer++), master_volume), volume);
                sample += *(stream);
                sample = (sample < -0x8000) ? -0x8000 : ((sample > 0x7FFF) ? 0x7FFF : sample);
                *(stream++) = sample;
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
            sound->Stop();
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