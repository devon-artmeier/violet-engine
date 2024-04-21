#include <SDL3/SDL.h>
#include "glad/glad.h"
#include "violet_audio_internal.hpp"
#include "violet_core_internal.hpp"
#include "violet_game_internal.hpp"
#include "violet_mesh_internal.hpp"
#include "violet_message_internal.hpp"
#include "violet_shader_internal.hpp"
#include "violet_texture_internal.hpp"
#include "violet_types.hpp"
#include "violet_video_internal.hpp"
#include "violet_window_internal.hpp"

namespace Violet
{
    void Initialize()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD) != 0) {
            Fatal((std::string)"Failed to initialize SDL2: " + SDL_GetError());
        }

        InitWindow();
        InitShaderManager();
        InitTextureManager();
        InitMeshManager();
        InitVideo();
        InitAudio();

        GameInit();
    }

    void Close()
    {
        GameClose();

        CloseAudio();
        CloseVideo();
        CloseMeshManager();
        CloseTextureManager();
        CloseShaderManager();
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