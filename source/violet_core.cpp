#include "violet_internal.hpp"

namespace Violet
{
    SDL_Window*     window  { nullptr };
    SDL_GLContext   gl      { nullptr };

    void Initialize()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD) != 0) {
            Fatal((std::string)"Failed to initialize SDL2: " + SDL_GetError());
        }
        
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    #if defined(__APPLE__)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    #endif
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        
        window = SDL_CreateWindow("", 640, 480, 0);
        if (window == nullptr) {
            Fatal((std::string)"Failed to create window: " + SDL_GetError());
        }
    }

    bool Update()
    {
        SDL_Event event;
        bool is_window_open = true;
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    is_window_open = false;
                    break;

                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    if (event.window.windowID == SDL_GetWindowID(window)) {
                        is_window_open = false;
                    }
                    break;
            }
        }
        
        return is_window_open;
    }

    void Close()
    {
        if (gl) SDL_GL_DeleteContext(gl);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Window* GetWindow()
    {
        return window;
    }
}