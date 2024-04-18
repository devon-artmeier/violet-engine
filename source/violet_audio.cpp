#include "violet_internal.hpp"

namespace Violet
{
    static SDL_AudioStream* audio_stream{ nullptr };

    static void AudioCallback(void *user_data, SDL_AudioStream *stream, int additional_amount, int total_amount)
    {

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
    }

    void CloseAudio()
    {
        if (audio_stream != nullptr) {
            SDL_PauseAudioDevice(SDL_GetAudioStreamDevice(audio_stream));
            SDL_CloseAudioDevice(SDL_GetAudioStreamDevice(audio_stream));
        }
    }
}