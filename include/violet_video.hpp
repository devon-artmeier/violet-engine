#ifndef VIOLET_ENGINE_VIDEO_HPP
#define VIOLET_ENGINE_VIDEO_HPP

namespace Violet
{
    extern void      EnableVideoMultisampling ();
    extern void      DisableVideoMultisampling();
    extern bool      IsVideoMultisampled      ();
    extern Matrix4x4 Get2dProjectionMatrix    ();
}

#endif // VIOLET_ENGINE_VIDEO_HPP