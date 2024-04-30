#include "violet_engine_internal.hpp"

namespace Violet
{
    static const char* sprite_shader_vertex =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec2 inVecCoord;\n"
        "layout (location = 1) in vec2 inTexCoord;\n"
        "\n"
        "uniform mat4 inProjection;\n"
        "uniform mat4 inTransform;\n"
        "out vec2 fragTexCoord;\n"
        "\n"
        "void main()\n"
        "{\n"
        "	gl_Position = inProjection * inTransform * vec4(inVecCoord, 0.0f, 1.0f);\n"
        "	fragTexCoord = inTexCoord;\n"
        "}";

    static const char* sprite_shader_frag =
        "#version 330 core\n"
        "\n"
        "in vec2 fragTexCoord;\n"
        "uniform sampler2D fragTexture;\n"
        "out vec4 outColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "	outColor = texture(fragTexture, fragTexCoord);\n"
        "}";

    static const char* text_shader_vertex =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec2 inVecCoord;\n"
        "layout (location = 1) in vec4 inColor;\n"
        "layout (location = 2) in vec2 inTexCoord;\n"
        "\n"
        "uniform mat4 inProjection;\n"
        "uniform mat4 inTransform;\n"
        "out vec4 fragColor;\n"
        "out vec2 fragTexCoord;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position  = inProjection * inTransform * vec4(inVecCoord, 0.0f, 1.0f);\n"
        "   fragColor    = inColor;\n"
        "   fragTexCoord = inTexCoord;\n"
        "}";

    static const char* text_shader_frag =
        "#version 330 core\n"
        "\n"
        "in vec4 fragColor;\n"
        "in vec2 fragTexCoord;\n"
        "uniform sampler2D fragTexture;\n"
        "out vec4 outColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   outColor = fragColor * vec4(1, 1, 1, texture(fragTexture, fragTexCoord).r);\n"
        "}";

    static bool multisampling{ false };

    void InitVideo()
    {
        LoadShaderInternal("shader_sprite_internal", sprite_shader_vertex, sprite_shader_frag);
        LoadShaderInternal("shader_text_internal", text_shader_vertex, text_shader_frag);

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