#include "glad/glad.h"
#include "violet_internal.hpp"

namespace Violet
{
    void Initialize()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD) != 0) {
            Fatal((std::string)"Failed to initialize SDL2: " + SDL_GetError());
        }

        InitWindow();
        InitVideo();
        InitAudio();
    }

    void Update()
    {
        ProcessWindowEvents();
        if (IsWindowOpen()) return;
    }

    void Close()
    {
        CloseAudio();
        CloseVideo();
        CloseWindow();

        SDL_Quit();
    }
}