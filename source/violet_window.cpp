#include "violet_engine_internal.hpp"

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

    uint GetWindowWidth()
    {
        int width;
        SDL_GetWindowSize(window, &width, nullptr);
        return static_cast<uint>(width);
    }

    uint GetWindowHeight()
    {
        int height;
        SDL_GetWindowSize(window, nullptr, &height);
        return static_cast<uint>(height);
    }

    UIVector2 GetWindowSize()
    {
        int width, height;
        SDL_GetWindowSize(window, &width, &height);
        return { static_cast<uint>(width), static_cast<uint>(height) };
    }
    
    uint GetWindowWidthPixels()
    {
        int width;
        SDL_GetWindowSizeInPixels(window, &width, nullptr);
        return static_cast<uint>(width);
    }

    uint GetWindowHeightPixels()
    {
        int height;
        SDL_GetWindowSizeInPixels(window, nullptr, &height);
        return static_cast<uint>(height);
    }

    UIVector2 GetWindowSizePixels()
    {
        int width, height;
        SDL_GetWindowSizeInPixels(window, &width, &height);
        return { static_cast<uint>(width), static_cast<uint>(height) };
    }
    
    void SetWindowWidth(const uint width)
    {
        SDL_SetWindowSize(window, width, GetWindowHeight());
    }
    
    void SetWindowHeight(const uint height)
    {
        SDL_SetWindowSize(window, GetWindowWidth(), height);
    }
    
    void SetWindowSize(const UIVector2& size)
    {
        SDL_SetWindowSize(window, size.X(), size.Y());
    }
    
    void SwapWindowBuffer()
    {
        SDL_GL_SwapWindow(window);
    }
}