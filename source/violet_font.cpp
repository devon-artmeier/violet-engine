#include "violet_engine_internal.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace Violet
{
    constexpr int AtlasWidth  = 1024;
    constexpr int AtlasHeight = 1024;

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
                stbtt_aligned_quad char_quad    = { 0 };
                Pointer<float>     vertex_data  = this->mesh->GetVertexBuffer();
                Pointer<uint>      element_data = this->mesh->GetElementBuffer();

                for (size_t i = 0; i < draw.text.length(); i++) {
                    stbtt_GetPackedQuad(this->packs[draw.size].Raw(), AtlasWidth, AtlasHeight, draw.text[i], &char_x, &char_y, &char_quad, 0);

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

                    *(element_data++) = (i * 4) + 0;
                    *(element_data++) = (i * 4) + 1;
                    *(element_data++) = (i * 4) + 2;
                    *(element_data++) = (i * 4) + 1;
                    *(element_data++) = (i * 4) + 2;
                    *(element_data++) = (i * 4) + 3;
                }

                this->mesh->RefreshVertexBuffer();
                this->mesh->RefreshElementBuffer();

                AttachShader("shader_text_internal");
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