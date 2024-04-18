#include <stdexcept>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "violet_internal.hpp"

#if defined(_DEBUG) && defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

int main(int argc, char** argv)
{
    try {
        Violet::Initialize();
        while (Violet::Update());
    } catch (std::exception& e) {
        MessageLog(Violet::MessageType::Fatal, e.what());
        MessageBox(Violet::MessageType::Fatal, e.what());
    }
    Violet::Close();

#if VIOLET_DEBUG==1 && defined(_MSC_VER)
    if (_CrtDumpMemoryLeaks()) {
        Violet::MessageBoxWarn("Memory leaks detected.");
    }
#endif
    
    return 0;
}