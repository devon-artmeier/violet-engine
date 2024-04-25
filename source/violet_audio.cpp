#include <SDL3/SDL.h>
#include "violet_audio_internal.hpp"
#include "violet_message_internal.hpp"

namespace Violet
{
    static SDL_AudioStream*    audio_stream { nullptr };
    static Pointer<SoundGroup> sound_group  { nullptr };
    static int                 master_volume{ 100 };

    static void AudioCallback(void *user_data, SDL_AudioStream *stream, int additional_amount, int total_amount)
    {
        if (additional_amount > 0) {
            Pointer<short> stream_data = new short[additional_amount / sizeof(short)];
            Pointer<short> read_buffer = new short[additional_amount / sizeof(short)];
            
            memset(stream_data.Raw(), 0, additional_amount);

            sound_group->Render(stream_data, read_buffer, additional_amount);
            SDL_PutAudioStreamData(stream, stream_data.Raw(), additional_amount);
        }
    }

    void InitAudio()
    {
        SDL_AudioSpec audio_spec  = { 0 };
        audio_spec.freq           = 44100;
        audio_spec.format         = SDL_AUDIO_S16;
        audio_spec.channels       = 2;

        audio_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_OUTPUT, &audio_spec, AudioCallback, nullptr);
        if (audio_stream == nullptr) {
            MessageBoxError("Failed to open audio device stream.");
        } else {
            SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(audio_stream));
        }

        sound_group = new SoundGroup();
    }

    void CloseAudio()
    {
        if (audio_stream != nullptr) {
            SDL_PauseAudioDevice(SDL_GetAudioStreamDevice(audio_stream));
            SDL_CloseAudioDevice(SDL_GetAudioStreamDevice(audio_stream));
        }
        sound_group = nullptr;
    }

    void LoadSound(const std::string& id, const std::string& path)
    {
        Pointer<Sound> sound = LoadWavSound("snd_" + id, path);
        if (sound->IsLoaded()) { sound_group->Add("snd_" + id, sound); return; }

        sound = LoadMp3Sound("snd_" + id, path);
        if (sound->IsLoaded()) { sound_group->Add("snd_" + id, sound); return; }

        sound = LoadOggSound("snd_" + id, path);
        if (sound->IsLoaded()) { sound_group->Add("snd_" + id, sound); return; }

        sound = LoadFlacSound("snd_" + id, path);
        if (sound->IsLoaded()) { sound_group->Add("snd_" + id, sound); return; }

#ifdef VIOLET_DEBUG
        LogError("snd_" + id + "\" from \"" + path + "\"");
#endif
    }

    void DestroySound(const std::string& id)
    {
        sound_group->Destroy("snd_" + id);
    }

    void PlaySound(const std::string& id, const uint play_count)
    {
        const Pointer<Sound>& sound = sound_group->Get("snd_" + id);
        if (sound != nullptr) {
            sound->Play(play_count);
        }
    }

    void StopSound(const std::string& id)
    {
        const Pointer<Sound>& sound = sound_group->Get("snd_" + id);
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
        if (this->loaded) {
            this->Stop();
        }
    }

    bool Sound::IsPlaying() const
    {
        return this->playing;
    }

    void Sound::Play(const uint play_count)
    {
        Seek(0);
        this->play_count    = play_count;
        this->play_position = 0;
        this->playing       = true;
    }

    void Sound::Stop()
    {
        if (this->playing) {
            this->playing       = false;
            this->play_position = 0;
            this->play_count    = 0;
        }
    }

    int Sound::GetVolume() const
    {
        return this->volume;
    }

    void Sound::SetVolume(const int volume)
    {
        this->volume = (volume < 0) ? 0 : ((volume > 100) ? 100 : volume);
    }

    static inline int ApplySampleVolume(const int sample, const int volume)
    {
        return (sample * volume) / 100;
    }

    void Sound::Render(Pointer<short> stream, Pointer<short> read_buffer, const size_t length)
    {
        if (this->playing) {
            size_t         read_count      = 0;
            Pointer<short> read_buffer_pos = read_buffer;
            bool           loop            = false;

            while (read_count < length) {
                size_t samples_to_read = length - read_count;
                if (this->play_count != 1 && this->loop_end != 0 && (this->loop_end - this->play_position) < samples_to_read) {
                    samples_to_read = this->loop_end - this->play_position;
                }

                int samples_read     = Read(read_buffer_pos, samples_to_read);
                this->play_position += samples_read;
                read_count          += samples_read;
                read_buffer_pos     += samples_read * 2;

                if (samples_read == 0) {
                    if (loop) break;
                    loop = true;
                } else {
                    loop = (this->loop_end != 0 && this->play_position >= this->loop_end);
                }

                if (loop) {
                    if (this->play_count == 1) break;
                    if (this->play_count > 1) {
                        this->play_count--;
                    }
                    this->play_position = this->loop_start;
                    Seek(this->loop_start);
                }
            }

            for (int i = 0; i < length * 2; i++) {
                int sample  = ApplySampleVolume(ApplySampleVolume(*(read_buffer++), master_volume), this->volume);
                sample     += *(stream);
                sample      = (sample < -0x8000) ? -0x8000 : ((sample > 0x7FFF) ? 0x7FFF : sample);
                *(stream++) = sample;
            }
        }
    }

    void SoundGroup::Render(const Pointer<short>& stream, const Pointer<short>& read_buffer, const size_t length) const
    {
        for (auto sound_entry : this->resources) {
            memset(read_buffer.Raw(), 0, length);
            sound_entry.second->Render(stream, read_buffer, length / (sizeof(short) * 2));
        }
    }
}