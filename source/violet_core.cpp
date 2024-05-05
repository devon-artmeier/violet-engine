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
        InitShaderGroup();
        InitTextureGroup();
        InitSpriteSheetGroup();
        InitFontGroup();
        InitAudio();

        GameInit();
    }

    void Close()
    {
        GameClose();

        CloseAudio();
        DestroyFontGroup();
        DestroySpriteSheetGroup();
        DestroyTextureGroup();
        DestroyShaderGroup();
        CloseVideo();
        CloseWindow();

        SDL_Quit();
    }

    void Update()
    {
        ProcessWindowEvents();
        if (!IsWindowOpen()) return;

        GameUpdate();
        UpdateVideo();
    }
}