#ifndef VIOLET_ENGINE_WINDOW_HPP
#define VIOLET_ENGINE_WINDOW_HPP

namespace Violet
{
    extern uint      GetWindowWidth       ();
    extern uint      GetWindowHeight      ();
    extern UIVector2 GetWindowSize        ();
    extern uint      GetWindowWidthPixels ();
    extern uint      GetWindowHeightPixels();
    extern UIVector2 GetWindowSizePixels  ();
    extern void      SetWindowWidth       (const uint width);
    extern void      SetWindowHeight      (const uint height);
    extern void      SetWindowSize        (const UIVector2& size);
}

#endif // VIOLET_ENGINE_WINDOW_HPP