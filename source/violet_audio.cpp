#include "violet_engine_internal.hpp"

#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>

#if defined(WIN32) && defined(APIENTRY)
#undef APIENTRY
#endif
#define MA_NO_DEVICE_IO
#define MA_NO_RUNTIME_LINKING
#ifdef VIOLET_DEBUG
#define MA_DEBUG_OUTPUT
#endif
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#if defined(WIN32) && defined(PlaySound)
#undef PlaySound
#endif

namespace Violet
{
    class Sound
    {
        public:
            Sound(const std::string& id, const std::string& path, ma_engine* engine)
            {
                this->id = id;
                LogInfo("Loading sound \"" + this->id + "\" from file \"" + path + "\"");

                if (ma_sound_init_from_file(engine, path.c_str(), MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, nullptr, &this->sound) == MA_SUCCESS) {
                    ma_sound_set_pan_mode(&this->sound, ma_pan_mode_pan);

                    LogInfo("Loaded sound \"" + this->id + "\" successfully");
                    this->loaded = true;
                } else {
                    LogError("Failed to load sound \"" + this->id + "\"");
                }
            }

            ~Sound()
            {
                ma_sound_uninit(&this->sound);
                LogInfo("Destroyed sound \"" + this->id + "\"");
            }

            std::string id    { "" };
            bool        loaded{ false };
            ma_sound    sound { { 0 } };
    };

    class AudioEngine
    {
        public:
            typedef std::unordered_map<std::string, Pointer<Sound>> SoundMap;

            AudioEngine()
            {
                ma_engine_config engine_config = { 0 };
                engine_config.channels         = 2;
                engine_config.sampleRate       = 44100;

                if (ma_engine_init(&engine_config, &this->engine) == MA_SUCCESS) {
                    this->initialized = true;
                } else {
                    MessageBoxError("Failed to initialize audio engine");
                }
            }

            ~AudioEngine()
            {
                sounds.clear();
                ma_engine_uninit(&this->engine);
            }

            bool      initialized{ false };
            ma_engine engine     { { 0 } };
            SoundMap  sounds;
    };

    static Pointer<AudioEngine> engine{ nullptr };
    static SDL_AudioStream*     stream{ nullptr };

    static void AudioCallback(void *user_data, SDL_AudioStream *stream, int additional_amount, int total_amount)
    {
        Pointer<uchar> buffer = new uchar[additional_amount];

        ma_uint64 frames = additional_amount / ma_get_bytes_per_frame(ma_format_f32, ma_engine_get_channels(&engine->engine));
        ma_engine_read_pcm_frames(&engine->engine, buffer.Raw(), frames, nullptr);

        SDL_PutAudioStreamData(stream, buffer.Raw(), additional_amount);
    }

    static Pointer<Sound> GetSound(const std::string& id)
    {
        auto sound = engine->sounds.find(id);

        if (sound != engine->sounds.end()) {
            return sound->second;
        }

        return nullptr;
    }

    void InitAudio()
    {
        engine = new AudioEngine;

        if (engine->initialized) {
            SDL_AudioSpec audio_spec = { 0 };

            audio_spec.freq     = ma_engine_get_sample_rate(&engine->engine);
            audio_spec.channels = ma_engine_get_channels(&engine->engine);
            audio_spec.format   = SDL_AUDIO_F32;

            stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_OUTPUT, &audio_spec, AudioCallback, nullptr);
            if (stream != nullptr) {
                SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(stream));
            } else {
                MessageBoxError("InitAudio: Failed to open audio device stream");
            }
        }
    }

    void CloseAudio()
    {
        SDL_PauseAudioDevice(SDL_GetAudioStreamDevice(stream));
        SDL_CloseAudioDevice(SDL_GetAudioStreamDevice(stream));
        engine = nullptr;
    }

    void LoadSound(const std::string& id, const std::string& path)
    {
        if (GetSound(id) == nullptr) {
            Pointer<Sound> sound = new Sound(id, path, &engine->engine);

            if (sound->loaded) {
                engine->sounds.insert({ id, sound });
            }
        } else {
            LogError("LoadSound: \"" + id + "\" is already loaded");
        }
    }

    void DestroySound(const std::string& id)
    {
        if (GetSound(id) != nullptr) {
            engine->sounds.erase(id);
        } else {
            LogError("DestroySound: \"" + id + "\" doesn't exist");
        }
    }

    void DestroyAllSounds()
    {
        engine->sounds.clear();
    }

    void PlaySound(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound != nullptr) {
            ma_sound_seek_to_pcm_frame(&sound->sound, 0);
            ma_sound_set_looping(&sound->sound, MA_FALSE);
            ma_sound_start(&sound->sound);
        } else {
            LogError("PlaySound: \"" + id + "\" doesn't exist");
        }
    }

    void LoopSound(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound != nullptr) {
            ma_sound_seek_to_pcm_frame(&sound->sound, 0);
            ma_sound_set_looping(&sound->sound, MA_TRUE);
            ma_sound_start(&sound->sound);
        } else {
            LogError("LoopSound: \"" + id + "\" doesn't exist");
        }
    }

    void StopSound(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound != nullptr) {
            ma_sound_stop(&sound->sound);
        } else {
            LogError("StopSound: \"" + id + "\" doesn't exist");
        }
    }

    bool IsSoundPlaying(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound == nullptr) {
            LogError("IsSoundPlaying: \"" + id + "\" doesn't exist");
            return false;
        }

        return ma_sound_is_playing(&sound->sound) == MA_TRUE;
    }

    bool IsSoundLooping(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound == nullptr) {
            LogError("IsSoundLooping: \"" + id + "\" doesn't exist");
            return false;
        }

        return IsSoundPlaying(id) && ma_sound_is_looping(&sound->sound) == MA_TRUE;
    }

    bool IsSoundAtEnd(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound == nullptr) {
            LogError("IsSoundAtEnd: \"" + id + "\" doesn't exist");
            return false;
        }

        return ma_sound_at_end(&sound->sound) == MA_TRUE;
    }

    float GetSoundVolume(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound == nullptr) {
            LogError("GetSoundVolume: \"" + id + "\" doesn't exist");
            return 0;
        }

        return ma_sound_get_volume(&sound->sound);
    }

    void SetSoundVolume(const std::string& id, const float volume)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound != nullptr) {
            ma_sound_set_volume(&sound->sound, volume);
        } else {
            LogError("SetSoundVolume: \"" + id + "\" doesn't exist");
        }
    }

    float GetSoundPanning(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound == nullptr) {
            LogError("GetSoundPanning: \"" + id + "\" doesn't exist");
            return 0;
        }

        return ma_sound_get_pan(&sound->sound);
    }

    void SetSoundPanning(const std::string& id, const float panning)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound != nullptr) {
            ma_sound_set_pan(&sound->sound, panning);
        } else {
            LogError("SetSoundPanning: \"" + id + "\" doesn't exist");
        }
    }

    float GetSoundPitch(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound != nullptr) {
            LogError("GetSoundPitch: \"" + id + "\" doesn't exist");
            return 0;
        }

        return ma_sound_get_pitch(&sound->sound);
    }

    void SetSoundPitch(const std::string& id, const float pitch)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound != nullptr) {
            ma_sound_set_pitch(&sound->sound, pitch);
        } else {
            LogError("SetSoundPitch: \"" + id + "\" doesn't exist");
        }
    }

    ulonglong GetSoundLength(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound == nullptr) {
            LogError("GetSoundLength: \"" + id + "\" doesn't exist");
            return 0;
        }

        ulonglong length;
        ma_sound_get_length_in_pcm_frames(&sound->sound, &length);
        return length;
    }

    ulonglong GetSoundLoopStart(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound == nullptr) {
            LogError("GetSoundLoopStart: \"" + id + "\" doesn't exist");
            return 0;
        }

        ulonglong point = 0;
        ma_data_source* data_source = ma_sound_get_data_source(&sound->sound);
        ma_data_source_get_loop_point_in_pcm_frames(&sound->sound, &point, nullptr);  
        return point;
    }

    ulonglong GetSoundLoopEnd(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound == nullptr) {
            LogError("GetSoundLoopEnd: \"" + id + "\" doesn't exist");
            return 0;
        }

        ulonglong point = 0;
        ma_data_source* data_source = ma_sound_get_data_source(&sound->sound);
        ma_data_source_get_loop_point_in_pcm_frames(&sound->sound, nullptr, &point);
        return point;
    }

    void SetSoundLoopStart(const std::string& id, const ulonglong point)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound != nullptr) {
            ma_data_source* data_source = ma_sound_get_data_source(&sound->sound);
            if (ma_data_source_set_loop_point_in_pcm_frames(data_source, point, GetSoundLoopEnd(id)) != MA_SUCCESS) {
                LogError("SetSoundLoopStart: Failed to set loop start point for \"" + id + "\"");
            }
        } else {
            LogError("SetSoundLoopStart: \"" + id + "\" doesn't exist");
        }
    }

    void SetSoundLoopEnd(const std::string& id, const ulonglong point)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound != nullptr) {
            ma_data_source* data_source = ma_sound_get_data_source(&sound->sound);
            if (ma_data_source_set_loop_point_in_pcm_frames(data_source, GetSoundLoopStart(id), point) != MA_SUCCESS) {
                LogError("SetSoundLoopEnd: Failed to set loop end point for \"" + id + "\"");
            }
        } else {
            LogError("SetSoundLoopEnd: \"" + id + "\" doesn't exist");
        }
    }

    void SetSoundLoop(const std::string& id, const ulonglong start, const ulonglong end)
    {
        Pointer<Sound> sound = GetSound(id);

        if (sound != nullptr) {
            ma_data_source* data_source = ma_sound_get_data_source(&sound->sound);
            if (ma_data_source_set_loop_point_in_pcm_frames(data_source, start, end) != MA_SUCCESS) {
                LogError("SetSoundLoop: Failed to set loop points for \"" + id + "\"");
            }
        } else {
            LogError("SetSoundLoop: \"" + id + "\" doesn't exist");
        }
    }

    float GetMasterVolume()
    {
        return ma_engine_get_volume(&engine->engine);
    }

    void SetMasterVolume(const float volume)
    {
        ma_engine_set_volume(&engine->engine, volume);
    }
}