#ifndef VIOLET_ENGINE_WINDOW_INTERNAL_HPP
#define VIOLET_ENGINE_WINDOW_INTERNAL_HPP

#include <SDL3/SDL.h>

namespace Violet
{
    extern void        InitWindow         ();
    extern void        CloseWindow        ();
    extern void        ProcessWindowEvents();
    extern SDL_Window* GetWindow          ();
    extern bool        IsWindowOpen       ();
    extern void        SwapWindowBuffer   ();
}

#endif // VIOLET_ENGINE_WINDOW_INTERNAL_HPP