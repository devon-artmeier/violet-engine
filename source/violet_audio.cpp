#include "violet_engine_internal.hpp"

namespace Violet
{
    static Pointer<AudioPlayer> player{ nullptr };

    static void AudioCallback(void *user_data, SDL_AudioStream *stream, int additional_amount, int total_amount)
    {
        Pointer<ma_uint8> buffer = new ma_uint8[additional_amount];
        player->Callback(buffer, additional_amount);
        SDL_PutAudioStreamData(stream, buffer.Raw(), additional_amount);
    }

    void InitAudio()
    {
        player = new AudioPlayer();
    }

    void CloseAudio()
    {
        DestroyAllSounds();
        player = nullptr;
    }

    void PlaySound(const std::string& id, const bool loop)
    {
        const Pointer<Sound>& sound = GetSound(id);
        if (sound != nullptr) {
            sound->Play(loop);
        }
    }

    void StopSound(const std::string& id)
    {
        const Pointer<Sound>& sound = GetSound(id);
        if (sound != nullptr) {
            sound->Stop();
        }
    }

    int GetSoundVolume(const std::string& id)
    {
        const Pointer<Sound>& sound = GetSound(id);
        if (sound != nullptr) {
            return sound->GetVolume();
        }
        return 0;
    }

    void SetSoundVolume(const std::string& id, const int volume)
    {
        const Pointer<Sound>& sound = GetSound(id);
        if (sound != nullptr) {
            sound->SetVolume(volume);
        }
    }

    ulonglong GetSoundLength(const std::string& id)
    {
        const Pointer<Sound>& sound = GetSound(id);
        if (sound != nullptr) {
            return sound->GetLength();
        }
        return 0;
    }

    ulonglong GetSoundLoopStart(const std::string& id)
    {
        const Pointer<Sound>& sound = GetSound(id);
        if (sound != nullptr) {
            return sound->GetLoopStart();
        }
        return 0;
    }

    ulonglong GetSoundLoopEnd(const std::string& id)
    {
        const Pointer<Sound>& sound = GetSound(id);
        if (sound != nullptr) {
            return sound->GetLoopEnd();
        }
        return 0;
    }

    void SetSoundLoopStart(const std::string& id, const ulonglong point)
    {
        const Pointer<Sound>& sound = GetSound(id);
        if (sound != nullptr) {
            sound->SetLoopStart(point);
        }
    }

    void SetSoundLoopEnd(const std::string& id, const ulonglong point)
    {
        const Pointer<Sound>& sound = GetSound(id);
        if (sound != nullptr) {
            sound->SetLoopEnd(point);
        }
    }

    void SetSoundLoop(const std::string& id, const ulonglong start, const ulonglong end)
    {
        const Pointer<Sound>& sound = GetSound(id);
        if (sound != nullptr) {
            sound->SetLoop(start, end);
        }
    }

    Sound::Sound(const std::string& id, const std::string& path)
    {
        this->id = id;
        if (player->InitSound(path, &this->sound)) {
            ma_sound_get_length_in_pcm_frames(&this->sound, &this->length);
            this->loaded = true;
        }
    }

    Sound::~Sound()
    {
        if (this->loaded) {
#ifdef VIOLET_DEBUG
            LogInfo(this->id + ": Destroyed");
#endif
        }
        ma_sound_uninit(&this->sound);
    }

    bool Sound::IsLoaded() const
    {
        return this->loaded;
    }

    bool Sound::IsPlaying() const
    {
        return ma_sound_is_playing(&this->sound) == MA_TRUE;
    }

    void Sound::Play(const bool loop)
    {
        ma_sound_seek_to_pcm_frame(&this->sound, 0);
        ma_sound_set_looping(&this->sound, loop ? MA_TRUE : MA_FALSE);
        ma_sound_start(&this->sound);
    }

    void Sound::Stop()
    {
        ma_sound_stop(&this->sound);
    }

    float Sound::GetVolume() const
    {
        return ma_sound_get_volume(&this->sound);
    }

    void Sound::SetVolume(const float volume)
    {
        ma_sound_set_volume(&this->sound, volume);
    }

    ulonglong Sound::GetLength()
    {
        return this->length;
    }

    ulonglong Sound::GetLoopStart()
    {
        ulonglong point = 0;
        ma_data_source* data_source = ma_sound_get_data_source(&this->sound);
        ma_data_source_get_loop_point_in_pcm_frames(&this->sound, &point, nullptr);
        return point;
    }

    ulonglong Sound::GetLoopEnd()
    {
        ulonglong point = 0;
        ma_data_source* data_source = ma_sound_get_data_source(&this->sound);
        ma_data_source_get_loop_point_in_pcm_frames(&this->sound, nullptr, &point);
        return point;
    }

    void Sound::SetLoopStart(const ulonglong point)
    {
        ma_data_source* data_source = ma_sound_get_data_source(&this->sound);
        if (ma_data_source_set_loop_point_in_pcm_frames(data_source, point, this->GetLoopEnd()) != MA_SUCCESS) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Failed to set loop start point");
#endif
        }
    }

    void Sound::SetLoopEnd(const ulonglong point)
    {
        ma_data_source* data_source = ma_sound_get_data_source(&this->sound);
        if (ma_data_source_set_loop_point_in_pcm_frames(data_source, this->GetLoopStart(), point) != MA_SUCCESS) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Failed to set loop end point");
#endif
        }
    }

    void Sound::SetLoop(const ulonglong start, const ulonglong end)
    {
        ma_data_source* data_source = ma_sound_get_data_source(&this->sound);
        if (ma_data_source_set_loop_point_in_pcm_frames(data_source, start, end) != MA_SUCCESS) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Failed to set loop points");
#endif
        }
    }

    AudioPlayer::AudioPlayer()
    {
        ma_engine_config engine_config = { 0 };
        engine_config.channels         = 2;
        engine_config.sampleRate       = 44100;

        if (ma_engine_init(&engine_config, &this->engine) != MA_SUCCESS) {
            MessageBoxError("Failed to initialize audio engine.");
            return;
        }

        SDL_AudioSpec audio_spec = { 0 };
        audio_spec.freq = ma_engine_get_sample_rate(&this->engine);
        audio_spec.channels = ma_engine_get_channels(&this->engine);
        audio_spec.format = SDL_AUDIO_F32;

        this->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_OUTPUT, &audio_spec, AudioCallback, nullptr);
        if (this->stream == nullptr) {
            MessageBoxError("Failed to open audio device stream.");
        } else {
            SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(this->stream));
        }
    }

    AudioPlayer::~AudioPlayer()
    {
        SDL_PauseAudioDevice(SDL_GetAudioStreamDevice(this->stream));
        SDL_CloseAudioDevice(SDL_GetAudioStreamDevice(this->stream));
        ma_engine_uninit(&this->engine);
    }

    bool AudioPlayer::InitSound(const std::string& path, ma_sound* sound)
    {
        return ma_sound_init_from_file(&this->engine, path.c_str(), 0, nullptr, nullptr, sound) == MA_SUCCESS;
    }

    void AudioPlayer::Callback(Pointer<ma_uint8> buffer, ma_uint64 length)
    {
        ma_uint64 frames = length / ma_get_bytes_per_frame(ma_format_f32, ma_engine_get_channels(&this->engine));
        ma_engine_read_pcm_frames(&this->engine, buffer.Raw(), frames, nullptr);
    }
}