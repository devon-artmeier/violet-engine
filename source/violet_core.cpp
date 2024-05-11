#include "violet_engine_internal.hpp"

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

        InitTextureGroup();
        InitShaderGroup();
        InitSpriteSheetGroup();
        InitFontGroup();

        GameInit();
    }

    void Close()
    {
        GameClose();

        DestroyFontGroup();
        DestroySpriteSheetGroup();
        DestroyShaderGroup();
        DestroyTextureGroup();

        CloseAudio();
        CloseVideo();
        CloseWindow();

        SDL_Quit();
    }

    void Update()
    {
        ProcessWindowEvents();

        if (IsWindowOpen()) {
            GameUpdate();
            UpdateVideo();
        }
    }
}