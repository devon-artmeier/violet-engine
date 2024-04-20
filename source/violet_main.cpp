#include <stdexcept>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "violet_engine.hpp"
#include "violet_core_internal.hpp"
#include "violet_message_internal.hpp"
#include "violet_window_internal.hpp"

#if defined(_DEBUG) && defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

int main(int argc, char** argv)
{
#ifdef VIOLET_DEBUG
#endif

    try {
        Violet::Initialize();
        while (Violet::IsWindowOpen()) {
            Violet::Update();
        }
    } catch (std::exception& e) {
#ifdef VIOLET_DEBUG
        MessageLog(Violet::MessageType::Fatal, e.what());
#endif
        MessageBox(Violet::MessageType::Fatal, e.what());
    }
    Violet::Close();

#if defined(VIOLET_DEBUG) && defined(_MSC_VER)
    if (_CrtDumpMemoryLeaks()) {
        Violet::MessageBoxWarn("Memory leaks detected.");
    }
#endif
    
    return 0;
}