#include "violet_engine_internal.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace Violet
{
    constexpr int AtlasWidth  = 1024;
    constexpr int AtlasHeight = 1024;

    static Pointer<Shader> text_shader{ nullptr };
    
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

    void InitText()
    {
        text_shader = new Shader("[INTERNAL] shader_text", text_shader_vertex, text_shader_frag);
    }

    void CloseText()
    {
        text_shader = nullptr;
    }

    void DrawText(const std::string& font_id, const uint size, const std::string& text, const uint layer, const float x, const float y, const Color color)
    {
        Pointer<Font> font = GetFont(font_id);
        if (font != nullptr) {
            font->QueueDraw(layer, { text, size, x, y, color });
        }
    }

    void DrawTextLayer(uint layer)
    {
        if (layer < 256) {
            for (auto font : GetAllFonts()) {
                font.second->DrawLayer(layer);
            }
        }
    }

	Font::Font(const std::string& id, const std::string& path)
	{
        this->id = id;

        Pointer<File> file = new File(path, false);
#ifdef VIOLET_DEBUG
            LogInfo(this->id + ": Loading \"" + path + "\"");
#endif

        if (!file->IsOpen()) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Failed to open");
#endif
            return;
        }

        Pointer<uchar> file_buffer = new uchar[file->GetSize()];
        file->ReadBuffer(file_buffer.Raw(), file->GetSize());
        if (file->Failed()) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Failed to read");
#endif
            return;
        }
        stbtt_InitFont(&font, file_buffer.Raw(), stbtt_GetFontOffsetForIndex(file_buffer.Raw(), 0));

        Pointer<uchar>     atlas        = new uchar[AtlasWidth * AtlasHeight * 4];
        stbtt_pack_context pack_context = {0};
        int                cur_texture  = 0;
        std::string        texture_id;

        stbtt_PackBegin(&pack_context, atlas.Raw(), AtlasWidth, AtlasHeight, AtlasWidth, 1, nullptr);
        
        for (float size = 1; size < 72; size++) {
            this->packs.insert({ static_cast<uint>(size), new stbtt_packedchar[256]});
            texture_id = this->id + "_texture_" + std::to_string(cur_texture);
            
            if (stbtt_PackFontRange(&pack_context, file_buffer.Raw(), 0, size, 0, 256, this->packs[size].Raw()) == 0) {
                LoadTexture(texture_id, atlas.Raw(), AtlasWidth, AtlasHeight, 1);
                cur_texture++;
                stbtt_PackEnd(&pack_context);
                
                stbtt_PackBegin(&pack_context, atlas.Raw(), AtlasWidth, AtlasHeight, AtlasWidth, 1, nullptr);
                if (stbtt_PackFontRange(&pack_context, file_buffer.Raw(), 0, size, 0, 256, this->packs[size].Raw()) == 0) {
                    break;
                }
            }

            float              char_x    = 0;
            float              char_y    = 0;
            stbtt_aligned_quad char_quad = { 0 };
            float              min_y     = 0;
            float              max_y     = 0;

            for (int i = 32; i < 127; i++) {
                stbtt_GetPackedQuad(this->packs[size].Raw(), AtlasWidth, AtlasHeight, i, &char_x, &char_y, &char_quad, 0);

                if (char_quad.y0 < min_y) {
                    min_y = char_quad.y0;
                }
                if (char_quad.y1 > max_y) {
                    max_y = char_quad.y1;
                }
            }

            this->heights.insert({ static_cast<uint>(size), max_y - min_y });
            this->textures.insert({ static_cast<uint>(size), texture_id });
        }

        LoadTexture(texture_id, atlas.Raw(), AtlasWidth, AtlasHeight, 1);
        stbtt_PackEnd(&pack_context);

        this->mesh = new Mesh(true, 0, 0, { 2, 4, 2 });

        loaded = true;
#ifdef VIOLET_DEBUG
        LogInfo(this->id + ": Loaded successfully");
#endif
    }

    Font::~Font()
    {
        if (this->loaded) {
#ifdef VIOLET_DEBUG
            LogInfo(this->id + ": Destroyed");
#endif
        }
    }

    bool Font::IsLoaded() const
    {
        return this->loaded;
    }

    void Font::QueueDraw(const uint layer, const FontDraw& draw)
    {
        if (layer < 256) {
            if (draw.size > 0 && draw.size < this->packs.size() - 1) {
                this->draw_queue[layer].push_back(draw);
            } else {
#ifdef VIOLET_DEBUG
                LogError(this->id + ": Attempted to draw text at invalid size " + std::to_string(draw.size));
#endif
            }
        }
    }

    void Font::DrawLayer(const uint layer)
    {
        if (layer < 256) {
            for (int i = 0; i < this->draw_queue[layer].size(); i++) {
                const FontDraw& draw = this->draw_queue[layer][i];

                this->mesh->ResizeVertexBuffer(draw.text.length() * 4, 0);
                this->mesh->ResizeElementBuffer(draw.text.length() * 6, 0);

                float              char_x       = 0;
                float              char_y       = 0;
                float              x_off        = 0;
                float              y_off        = this->heights[draw.size];
                bool               new_line     = false;
                int                element_id   = 0;
                stbtt_aligned_quad char_quad    = { 0 };
                Pointer<float>     vertex_data  = this->mesh->GetVertexBuffer();
                Pointer<uint>      element_data = this->mesh->GetElementBuffer();

                for (size_t i = 0; i < draw.text.length(); i++) {
                    if (draw.text[i] == '\n') {
                        new_line  = true;
                        y_off    += this->heights[draw.size];
                    } else if (draw.text[i] == '\r') {
                        new_line = true;
                    } else {
                        stbtt_GetPackedQuad(this->packs[draw.size].Raw(), AtlasWidth, AtlasHeight, draw.text[i], &char_x, &char_y, &char_quad, 0);

                        if (new_line) {
                            x_off    = -char_quad.x0;
                            new_line = false;
                        }

                        char_quad.x0 += x_off;
                        char_quad.x1 += x_off;
                        char_quad.y0 += y_off;
                        char_quad.y1 += y_off;

                        *(vertex_data++) = char_quad.x0;
                        *(vertex_data++) = char_quad.y0;
                        *(vertex_data++) = draw.color.red / 255.0f;
                        *(vertex_data++) = draw.color.green / 255.0f;
                        *(vertex_data++) = draw.color.blue / 255.0f;
                        *(vertex_data++) = draw.color.alpha / 255.0f;
                        *(vertex_data++) = char_quad.s0;
                        *(vertex_data++) = char_quad.t0;

                        *(vertex_data++) = char_quad.x1;
                        *(vertex_data++) = char_quad.y0;
                        *(vertex_data++) = draw.color.red / 255.0f;
                        *(vertex_data++) = draw.color.green / 255.0f;
                        *(vertex_data++) = draw.color.blue / 255.0f;
                        *(vertex_data++) = draw.color.alpha / 255.0f;
                        *(vertex_data++) = char_quad.s1;
                        *(vertex_data++) = char_quad.t0;

                        *(vertex_data++) = char_quad.x0;
                        *(vertex_data++) = char_quad.y1;
                        *(vertex_data++) = draw.color.red / 255.0f;
                        *(vertex_data++) = draw.color.green / 255.0f;
                        *(vertex_data++) = draw.color.blue / 255.0f;
                        *(vertex_data++) = draw.color.alpha / 255.0f;
                        *(vertex_data++) = char_quad.s0;
                        *(vertex_data++) = char_quad.t1;

                        *(vertex_data++) = char_quad.x1;
                        *(vertex_data++) = char_quad.y1;
                        *(vertex_data++) = draw.color.red / 255.0f;
                        *(vertex_data++) = draw.color.green / 255.0f;
                        *(vertex_data++) = draw.color.blue / 255.0f;
                        *(vertex_data++) = draw.color.alpha / 255.0f;
                        *(vertex_data++) = char_quad.s1;
                        *(vertex_data++) = char_quad.t1;

                        *(element_data++) = element_id + 0;
                        *(element_data++) = element_id + 1;
                        *(element_data++) = element_id + 2;
                        *(element_data++) = element_id + 1;
                        *(element_data++) = element_id + 2;
                        *(element_data++) = element_id + 3;
                        element_id += 4;
                    }
                }

                this->mesh->RefreshVertexBuffer();
                this->mesh->RefreshElementBuffer();

                text_shader->Attach();
                SetShaderMatrix4x4("inProjection", false, 1, glm::value_ptr(Get2dProjectionMatrix()));
                SetShaderMatrix4x4("inTransform", false, 1,
                    glm::value_ptr(Get2dTransformMatrix(draw.x, draw.y, 1.0f, 1.0f, 0.0f)));
                SetShaderTexture(this->textures[draw.size], 0);

                this->mesh->Draw();
            }
            this->draw_queue[layer].clear();
        }
    }
}