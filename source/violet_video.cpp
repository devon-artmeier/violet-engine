#include <glad.h>
#include "violet_video_internal.hpp"
#include "violet_window_internal.hpp"

#include "violet_sprite_internal.hpp"
#include "violet_texture.hpp"

namespace Violet
{
    static Pointer<SpriteSheet> sheet = nullptr;
    
    void InitVideo()
    {
        LoadTexture("texture", "texture.png");
        sheet = new SpriteSheet("test", "sprites.spr", "texture");
    }

    void CloseVideo()
    {
        sheet = nullptr;
    }

    void UpdateVideo()
    {
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        sheet->Draw(0);
        
        SwapWindowBuffer();
    }
}