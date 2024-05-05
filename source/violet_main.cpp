#include "violet_engine_internal.hpp"
#include <SDL3/SDL_main.h>

#if defined(_DEBUG) && defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

int main(int argc, char** argv)
{
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