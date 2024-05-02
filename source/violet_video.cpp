#include "violet_engine_internal.hpp"

namespace Violet
{
    static bool multisampling{ false };

    void InitVideo()
    {
        UpdateProjectionMatrices();
        EnableVideoMultisampling();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void CloseVideo()
    {

    }

    void UpdateVideo()
    {
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        for (uint i = 0; i < 256; i++) {
            DrawSpriteLayer(i);
            DrawTextLayer(i);
        }

        SwapWindowBuffer();
    }

    void EnableVideoMultisampling()
    {
        if (multisampling == false) {
            glEnable(GL_MULTISAMPLE);
            multisampling = true;
        }
    }

    void DisableVideoMultisampling()
    {
        if (multisampling == true) {
            glDisable(GL_MULTISAMPLE);
            multisampling = false;
        }
    }

    bool IsVideoMultisampled()
    {
        return multisampling;
    }
}