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
                LogInfo(this->id + ": Loading \"" + path + "\"");

                ma_result result = ma_sound_init_from_file(engine, path.c_str(), MA_SOUND_FLAG_NO_SPATIALIZATION, nullptr, nullptr, &this->sound);

                if (Assert(result == MA_SUCCESS, this->id + ": Failed to load")) {
                    ma_sound_set_pan_mode(&this->sound, ma_pan_mode_pan);
                    LogInfo(id + ": Loaded successfully");
                    this->loaded = true;
                }
            }

            ~Sound()
            {
                ma_sound_uninit(&this->sound);
                LogInfo(this->id + ": Destroyed");
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

                ma_result result = ma_engine_init(&engine_config, &this->engine);

                if (Assert(result == MA_SUCCESS, "Failed to initialize audio engine", true)) {
                    this->initialized = true;
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

            if (Assert(stream != nullptr, "Failed to open audio device stream", true)) {
                SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(stream));
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
        if (Assert(GetSound(id) == nullptr, id + ": Already loaded")) {
            Pointer<Sound> sound = new Sound(id, path, &engine->engine);

            if (sound->loaded) {
                engine->sounds.insert({ id, sound });
            }
        }
    }

    void DestroySound(const std::string& id)
    {
        if (Assert(GetSound(id) != nullptr, id + ": Doesn't exist")) {
            engine->sounds.erase(id);
        }
    }

    void DestroyAllSounds()
    {
        engine->sounds.clear();
    }

    void PlaySound(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (Assert(sound != nullptr, id + ": Doesn't exist")) {
            LogInfo(id + ": Playing");

            ma_sound_seek_to_pcm_frame(&sound->sound, 0);
            ma_sound_set_looping(&sound->sound, MA_FALSE);
            ma_sound_start(&sound->sound);
        }
    }

    void LoopSound(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (Assert(sound != nullptr, id + ": Doesn't exist")) {
            LogInfo(id + ": Looping");

            ma_sound_seek_to_pcm_frame(&sound->sound, 0);
            ma_sound_set_looping(&sound->sound, MA_TRUE);
            ma_sound_start(&sound->sound);
        }
    }

    void StopSound(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (Assert(sound != nullptr, id + ": Doesn't exist")) {
            LogInfo(id + ": Stopped");
            ma_sound_stop(&sound->sound);
        }
    }

    bool IsSoundPlaying(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (!Assert(sound != nullptr, id + ": Doesn't exist")) {
            return false;
        }

        return ma_sound_is_playing(&sound->sound) == MA_TRUE;
    }

    bool IsSoundLooping(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (!Assert(sound != nullptr, id + ": Doesn't exist")) {
            return false;
        }

        return IsSoundPlaying(id) && ma_sound_is_looping(&sound->sound) == MA_TRUE;
    }

    bool IsSoundAtEnd(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (!Assert(sound != nullptr, id + ": Doesn't exist")) {
            return false;
        }

        return ma_sound_at_end(&sound->sound) == MA_TRUE;
    }

    float GetSoundVolume(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (!Assert(sound != nullptr, id + ": Doesn't exist")) {
            return 0;
        }

        return ma_sound_get_volume(&sound->sound);
    }

    void SetSoundVolume(const std::string& id, const float volume)
    {
        Pointer<Sound> sound = GetSound(id);

        if (Assert(sound != nullptr, id + ": Doesn't exist")) {
            ma_sound_set_volume(&sound->sound, volume);
        }
    }

    float GetSoundPanning(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);

        if (!Assert(sound != nullptr, id + ": Doesn't exist")) {
            return 0;
        }

        return ma_sound_get_pan(&sound->sound);
    }

    void SetSoundPanning(const std::string& id, const float panning)
    {
        Pointer<Sound> sound = GetSound(id);

        if (Assert(sound != nullptr, id + ": Doesn't exist")) {
            ma_sound_set_pan(&sound->sound, panning);
        }
    }

    float GetSoundPitch(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);
        
        if (!Assert(sound != nullptr, id + ": Doesn't exist")) {
            return 0;
        }

        return ma_sound_get_pitch(&sound->sound);
    }

    void SetSoundPitch(const std::string& id, const float pitch)
    {
        Pointer<Sound> sound = GetSound(id);
        
        if (Assert(sound != nullptr, id + ": Doesn't exist")) {
            ma_sound_set_pitch(&sound->sound, pitch);
        }
    }

    ulonglong GetSoundLength(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);
        
        if (!Assert(sound != nullptr, id + ": Doesn't exist")) {
            return 0;
        }

        ulonglong length;
        ma_sound_get_length_in_pcm_frames(&sound->sound, &length);
        return length;
    }

    ulonglong GetSoundLoopStart(const std::string& id)
    {
        Pointer<Sound> sound = GetSound(id);
        
        if (!Assert(sound != nullptr, id + ": Doesn't exist")) {
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
        
        if (!Assert(sound != nullptr, id + ": Doesn't exist")) {
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
        
        if (Assert(sound != nullptr, id + ": Doesn't exist")) {
            ma_data_source* data_source = ma_sound_get_data_source(&sound->sound);
            ma_result result = ma_data_source_set_loop_point_in_pcm_frames(data_source, point, GetSoundLoopEnd(id));
            
            if (Assert(result == MA_SUCCESS, id + ": Failed to set loop start point")) {
                LogInfo(id + ": Set loop start point to " + std::to_string(point));
            }
        }
    }

    void SetSoundLoopEnd(const std::string& id, const ulonglong point)
    {
        Pointer<Sound> sound = GetSound(id);
        
        if (sound != nullptr) {
            ma_data_source* data_source = ma_sound_get_data_source(&sound->sound);
            ma_result result = ma_data_source_set_loop_point_in_pcm_frames(data_source, GetSoundLoopStart(id), point);
            
            if (Assert(result == MA_SUCCESS, id + ": Failed to set loop end point")) {
                LogInfo(id + ": Set loop end point to " + std::to_string(point));
            }
        }
    }

    void SetSoundLoop(const std::string& id, const ulonglong start, const ulonglong end)
    {
        Pointer<Sound> sound = GetSound(id);
       
        if (sound != nullptr) {
            ma_data_source* data_source = ma_sound_get_data_source(&sound->sound);
            ma_result result = ma_data_source_set_loop_point_in_pcm_frames(data_source, start, end);

            if (Assert(result == MA_SUCCESS, id + ": Failed to set loop points")) {
                LogInfo(id + ": Set loop points to " + std::to_string(start) + " and " + std::to_string(end));
            }
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