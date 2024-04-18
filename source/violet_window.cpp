#include "glad/glad.h"
#include "violet_internal.hpp"

namespace Violet
{
    static SDL_Window*      window  { nullptr };
    static SDL_GLContext    gl      { nullptr };

    void InitWindow()
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#ifdef __APPLE__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        window = SDL_CreateWindow("", 640, 480, SDL_WINDOW_OPENGL);
        if (window == nullptr) {
            Fatal((std::string)"Failed to create window: " + SDL_GetError());
        }
        
        gl = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, gl);
        SDL_GL_SetSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            Fatal("Failed to initialize OpenGL.");
        }
    }

    void CloseWindow()
    {
        if (gl != nullptr) {
            SDL_GL_DeleteContext(gl);
            gl = nullptr;
        }

        if (window != nullptr) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
    }

    void ProcessWindowEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    CloseWindow();
                    break;
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    if (event.window.windowID == SDL_GetWindowID(window)) {
                        CloseWindow();
                    }
                    break;
            }
        }
    }

    SDL_Window* GetWindow()
    {
        return window;
    }

    bool IsWindowOpen()
    {
        return window != nullptr;
    }

    void SwapWindowBuffer()
    {
        SDL_GL_SwapWindow(window);
    }
}