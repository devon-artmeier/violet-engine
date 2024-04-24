#include <glad.h>
#include "violet_video_internal.hpp"
#include "violet_window_internal.hpp"

#include "violet_shader_internal.hpp"
#include "violet_sprite_internal.hpp"
#include "violet_texture.hpp"

static const char* vertex_shader =
	"#version 330 core\n"
	""
	"layout (location = 0) in vec2 inVecCoord;\n"
	"layout (location = 1) in vec2 inTexCoord;\n"
	""
	"out vec2 fragTexCoord;\n"
	""
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(inVecCoord, 0.0f, 1.0f);\n"
	"	fragTexCoord = inTexCoord;\n"
	"}";

static const char* frag_shader =
	"#version 330 core\n"
	""
	"in vec2 fragTexCoord;\n"
	"out vec4 outColor;\n"
	"uniform sampler2D fragTexture;\n"
	""
	"void main()\n"
	"{\n"
	"	outColor = texture(fragTexture, fragTexCoord);\n"
	"}";

namespace Violet
{
    static Pointer<SpriteSheet> sheet = nullptr;
    
    void InitVideo()
    {
        LoadShader("shader", vertex_shader, frag_shader);
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
        
        AttachShader("shader");
        SetShaderTexture("texture", 0);
        sheet->Draw(0);
        
        SwapWindowBuffer();
    }
}