#include "glad/glad.h"
#include "violet_internal.hpp"

namespace Violet
{
    static SDL_GLContext gl{ nullptr };

    void InitVideo()
    {
        gl = SDL_GL_CreateContext(GetWindow());
        SDL_GL_MakeCurrent(GetWindow(), gl);
        SDL_GL_SetSwapInterval(0);

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            Fatal("Failed to initialize OpenGL.");
        }
    }

    void CloseVideo()
    {
        if (gl != nullptr) {
            SDL_GL_DeleteContext(gl);
            gl = nullptr;
        }
    }
}