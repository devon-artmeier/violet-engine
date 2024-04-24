#ifndef VIOLET_ENGINE_WINDOW_HPP
#define VIOLET_ENGINE_WINDOW_HPP

namespace Violet
{
    extern int  GetWindowWidth       ();
    extern int  GetWindowHeight      ();
    extern void GetWindowSize        (int& width, int& height);
    extern int  GetWindowWidthPixels ();
    extern int  GetWindowHeightPixels();
    extern void GetWindowSizePixels  (int& width, int& height);
    extern void SetWindowWidth       (const int width);
    extern void SetWindowHeight      (const int height);
    extern void SetWindowSize        (const int width, const int height);
}

#endif // VIOLET_ENGINE_WINDOW_HPP