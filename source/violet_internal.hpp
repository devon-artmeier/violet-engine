#ifndef VIOLET_ENGINE_INTERNAL_HPP
#define VIOLET_ENGINE_INTERNAL_HPP

#include <SDL3/SDL.h>
#include "violet_engine.hpp"

namespace Violet
{
    enum class MessageType {
        Info,
        Warn,
        Error,
        Fatal
    };
    
    extern void         Initialize();
    extern void         Close();
    extern void         Update();
    
    extern void         MessageLog(const MessageType type, const std::string& message);
    extern void         MessageBox(const MessageType type, const std::string& message);
    
    extern void         InitVideo();
    extern void         CloseVideo();
    extern void         UpdateVideo();

    extern void         InitAudio();
    extern void         CloseAudio();

    extern void         InitWindow();
    extern void         CloseWindow();
    extern void         ProcessWindowEvents();
    extern SDL_Window*  GetWindow();
    extern bool         IsWindowOpen();
    extern void         SwapWindowBuffer();

    extern void         GameInit();
    extern void         GameUpdate();
    extern void         GameFixedUpdate();
    extern void         GameClose();
}

#endif // VIOLET_ENGINE_INTERNAL_HPP