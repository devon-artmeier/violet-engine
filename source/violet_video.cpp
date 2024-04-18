#include "glad/glad.h"
#include "violet_internal.hpp"

namespace Violet
{

    void InitVideo()
    {

    }

    void CloseVideo()
    {

    }

    void UpdateVideo()
    {
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        SwapWindowBuffer();
    }
}