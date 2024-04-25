#include <string>
#include <SDL3/SDL.h>
#include <glad.h>
#include "violet_message_internal.hpp"
#include "violet_window_internal.hpp"

namespace Violet
{
    static SDL_Window*   window{ nullptr };
    static SDL_GLContext gl    { nullptr };

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
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

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

    int GetWindowWidth()
    {
        int width;
        SDL_GetWindowSize(window, &width, nullptr);
        return width;
    }

    int GetWindowHeight()
    {
        int height;
        SDL_GetWindowSize(window, nullptr, &height);
        return height;
    }

    void GetWindowSize(int& width, int& height)
    {
        SDL_GetWindowSize(window, &width, &height);
    }
    
    int GetWindowWidthPixels()
    {
        int width;
        SDL_GetWindowSizeInPixels(window, &width, nullptr);
        return width;
    }

    int GetWindowHeightPixels()
    {
        int height;
        SDL_GetWindowSizeInPixels(window, nullptr, &height);
        return height;
    }

    void GetWindowSizePixels(int& width, int& height)
    {
        SDL_GetWindowSizeInPixels(window, &width, &height);
    }
    
    void SetWindowWidth(const int width)
    {
        SDL_SetWindowSize(window, width, GetWindowHeight());
    }
    
    void SetWindowHeight(const int height)
    {
        SDL_SetWindowSize(window, GetWindowWidth(), height);
    }
    
    void SetWindowSize(const int width, const int height)
    {
        SDL_SetWindowSize(window, width, height);
    }
    
    void SwapWindowBuffer()
    {
        SDL_GL_SwapWindow(window);
    }
}