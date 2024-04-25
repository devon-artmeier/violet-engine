#include <glad.h>
#include "violet_sprite_internal.hpp"
#include "violet_video_internal.hpp"
#include "violet_window_internal.hpp"

namespace Violet
{
    static bool multisampling{ false };

    void InitVideo()
    {
        EnableVideoMultisampling();
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