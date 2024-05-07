#include "violet_engine_internal.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

namespace Violet
{
    constexpr int AtlasWidth  = 1024;
    constexpr int AtlasHeight = 1024;

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

    class FontGroup
    {
        public:
            std::unordered_map<std::string, Pointer<Font>> fonts;
    };

    static Pointer<FontGroup> font_group { nullptr };
    static Pointer<Shader>    text_shader{ nullptr };

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
        Pointer<Texture>   texture      = new Texture(this->id + " Texture 0", nullptr, AtlasWidth, AtlasHeight, 1);
        int                cur_texture  = 0;

        stbtt_PackBegin(&pack_context, atlas.Raw(), AtlasWidth, AtlasHeight, AtlasWidth, 1, nullptr);
        
        for (float size = 1; size < 72; size++) {
            this->packs.insert({ static_cast<uint>(size), new stbtt_packedchar[256]});
            
            if (stbtt_PackFontRange(&pack_context, file_buffer.Raw(), 0, size, 0, 256, this->packs[size].Raw()) == 0) {
                texture->UpdatePixels(atlas.Raw(), AtlasWidth, AtlasHeight, 1, 0, 0);
                texture = new Texture(this->id + " Texture " + std::to_string(++cur_texture), nullptr, AtlasWidth, AtlasHeight, 1);
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
            this->textures.insert({ static_cast<uint>(size), texture });
        }

        texture->UpdatePixels(atlas.Raw(), AtlasWidth, AtlasHeight, 1, 0, 0);
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

    void InitFontGroup()
    {
        text_shader = new Shader("Default Text Shader", text_shader_vertex, text_shader_frag);
        font_group  = new FontGroup();
    }

    void DestroyFontGroup()
    {
        font_group  = nullptr;
        text_shader = nullptr;
    }

    static Pointer<Font> GetFont(const std::string& id)
    {
        auto font = font_group->fonts.find(id);
        if (font != font_group->fonts.end()) {
            return font->second;
        }
        return Pointer<Font>(nullptr);
    }

    void LoadFont(const std::string& id, const std::string& path)
    {
        if (GetFont(id) == nullptr) {
            Pointer<Font> font = new Font(id, path);
            if (font->loaded) {
                font_group->fonts.insert({ id, font });
            }
        }
    }

    void DestroyFont(const std::string& id)
    {
        if (GetFont(id) != nullptr) {
            font_group->fonts.erase(id);
        }
    }

    void DestroyAllFonts()
    {
        font_group->fonts.clear();
    }

    void DrawText(const std::string& font_id, const uint size, const std::string& text, const uint layer, const Vector2& pos, const Color color)
    {
        Pointer<Font> font = GetFont(font_id);
        if (font != nullptr) {
            if (size > 0 && size < font->packs.size() - 1) {
                font->draw_queue[layer].push_back({ text, size, pos, color });
            } else {
#ifdef VIOLET_DEBUG
                LogError(font_id + ": Attempted to draw text at invalid size " + std::to_string(size));
#endif
            }
        }
    }

    void DrawTextLayer(uint layer)
    {
        if (layer < 256) {
            for (auto font_pair : font_group->fonts) {
                Pointer<Font> font = font_pair.second;

                for (int i = 0; i < font->draw_queue[layer].size(); i++) {
                    const FontDraw& draw = font->draw_queue[layer][i];

                    font->mesh->ResizeVertexBuffer(draw.text.length() * 4, 0);
                    font->mesh->ResizeElementBuffer(draw.text.length() * 6, 0);

                    float              char_x       = 0;
                    float              char_y       = 0;
                    float              x_off        = 0;
                    float              y_off        = font->heights[draw.size];
                    bool               new_line     = false;
                    int                element_id   = 0;
                    stbtt_aligned_quad char_quad    = { 0 };
                    Pointer<float>     vertex_data  = font->mesh->GetVertexBuffer();
                    Pointer<uint>      element_data = font->mesh->GetElementBuffer();

                    for (size_t i = 0; i < draw.text.length(); i++) {
                        if (draw.text[i] == '\n') {
                            new_line  = true;
                            y_off    += font->heights[draw.size];
                        } else if (draw.text[i] == '\r') {
                            new_line = true;
                        } else {
                            stbtt_GetPackedQuad(font->packs[draw.size].Raw(), AtlasWidth, AtlasHeight, draw.text[i], &char_x, &char_y, &char_quad, 0);

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

                    font->mesh->RefreshVertexBuffer();
                    font->mesh->RefreshElementBuffer();

                    text_shader->Attach();
                    SetShaderMatrix4x4("inProjection", Get2dProjectionMatrix());
                    SetShaderMatrix4x4("inTransform", TransformMatrix(draw.pos, 0.0f, Vector2(1.0f)));
                    SetShaderTexture(font->textures[draw.size], 0);

                    font->mesh->Draw();
                }

                font->draw_queue[layer].clear();
            }
        }
    }
}