#include "violet_engine_internal.hpp"

namespace Violet
{
    static bool      multisampling{ false };
    static Matrix4x4 projection_2d;

    void InitVideo()
    {
        EnableVideoMultisampling();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void CloseVideo()
    {

    }

    void UpdateVideo()
    {
        projection_2d = OrthoMatrix(Vector2(0.0f, static_cast<float>(GetWindowWidthPixels())),
                                    Vector2(0.0f, static_cast<float>(GetWindowHeightPixels())));
        glViewport(0, 0, static_cast<float>(GetWindowWidthPixels()), static_cast<float>(GetWindowHeightPixels()));

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

    Matrix4x4 Get2dProjectionMatrix()
    {
        return projection_2d;
    }
}