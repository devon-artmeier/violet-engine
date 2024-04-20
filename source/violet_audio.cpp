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
                memset(read_buffer, 0, additional_amount);

                sound_manager->Render(reinterpret_cast<short*>(stream_data),
                                      reinterpret_cast<short*>(read_buffer),
                                      additional_amount / (sizeof(short) * 2));
                                      
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

    void PlaySound(const std::string& id)
    {
        Sound* sound = sound_manager->GetSound(id);
        if (sound != nullptr) {
            sound->Play(0);
        }
    }

    void LoopSound(const std::string& id, const int loop_count)
    {
        Sound* sound = sound_manager->GetSound(id);
        if (sound != nullptr) {
            sound->Play((loop_count > 0) ? loop_count : -1);
        }
    }

    void Sound::Play(const int loop_count)
    {
        if (IsOpened()) {
            this->playing = true;
            this->loop_count = loop_count;
        }
    }

    void Sound::Stop()
    {
        this->playing = false;
    }

    bool Sound::IsPlaying()
    {
        return playing;
    }

    SoundManager::~SoundManager()
    {
        CloseAllSounds();
    }

    void SoundManager::Render(short* stream, short* read_buffer, const size_t length)
    {
        for (auto sound_entry : sounds) {
            Sound* sound = sound_entry.second;
            if (sound->IsOpened() && sound->IsPlaying()) {
                sound->Render(stream, read_buffer, length);
            }
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