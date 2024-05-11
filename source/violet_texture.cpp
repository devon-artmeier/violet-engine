#include "violet_engine_internal.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Violet
{
    class TextureGroup
    {
        public:
            typedef std::unordered_map<std::string, Pointer<Texture>> TextureMap;

            TextureMap textures;
            GLuint     current_texture{ 0 };
    };

    static Pointer<TextureGroup> texture_group{ nullptr };

    static GLenum GetBppFormat(const uint bpp, const std::string& id)
    {
        if (Assert(bpp >= 1 && bpp <= 4, "Invalid bits per pixel \"" + std::to_string(bpp) + "\" used when loading data into texture \"" + id + "\"")) {
            switch (bpp) {
                case 1:
                    return GL_RED;
                case 2:
                    return GL_RG;
                case 3:
                    return GL_RGB;
                case 4:
                    return GL_RGBA;
            }
        }
        return GL_RGBA;
    }

    Texture::Texture(const std::string& id, const std::string& path)
    {
        this->id = id;
        LogInfo("Loading texture \"" + this->id + "\" from file \"" + path + "\"");

        int width, height;
        uchar* data = stbi_load(path.c_str(), &width, &height, nullptr, 4);
        this->size.X() = static_cast<uint>(width);
        this->size.Y() = static_cast<uint>(height);

        if (Assert(data != nullptr, "Failed to load texture \"" + this->id + "\"" + (stbi_failure_reason() != nullptr ? (std::string)":\n" + stbi_failure_reason() : ""))) {
            glGenTextures(1, &this->texture);
            this->Bind();

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->size.X(), this->size.Y(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);

            LogInfo("Loaded texture \"" + this->id + "\" successfully");
        }
    }

    Texture::Texture(const std::string& id, const void* const data, const UIVector2& size, const uint bpp)
    {
        this->id = id;
        LogInfo("Loading texture \"" + this->id + "\"");

        glGenTextures(1, &this->texture);
        this->Bind();
        this->size = size;

        GLenum format = GetBppFormat(bpp, this->id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, this->size.X(), this->size.Y(), 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

        LogInfo("Loaded texture \"" + this->id + "\" successfully");
    }

    Texture::~Texture()
    {
        if (this->texture != 0) {
            if (texture_group->current_texture == this->texture) {
                texture_group->current_texture = 0;
            }
            glDeleteTextures(1, &this->texture);
        }
        LogInfo("Destroyed texture \"" + this->id + "\"");
    }

    void Texture::Bind()
    {
        if (texture_group->current_texture != this->texture) {
            texture_group->current_texture = this->texture;
            glBindTexture(GL_TEXTURE_2D, this->texture);
        }
    }

    void Texture::UpdatePixels(const void* const data, const UIVector2& size, const uint bpp, const int x, const int y)
    {
        this->Bind();
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, this->size.X(), this->size.Y(), GetBppFormat(bpp, this->id), GL_UNSIGNED_BYTE, data);
    }

    void Texture::SetFilter(const TextureFilter filter)
    {
        if (this->filter != filter) {
            this->filter = filter;

            this->Bind();
            switch (filter) {
                case TextureFilter::Nearest:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    break;
                case TextureFilter::Bilinear:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    break;
            }
        }
    }

    static GLint GetGlWrapValue(const TextureWrap wrap)
    {
        switch (wrap) {
            case TextureWrap::Mirror:
                return GL_MIRRORED_REPEAT;
            case TextureWrap::ClampEdge:
                return GL_CLAMP_TO_EDGE;
            case TextureWrap::ClampBorder:
                return GL_CLAMP_TO_BORDER;
        }
        return GL_REPEAT;
    }

    void Texture::SetWrapX(const TextureWrap wrap)
    {
        if (this->wrap_x != wrap) {
            this->wrap_x = wrap;

            this->Bind();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGlWrapValue(wrap));
        }
    }

    void Texture::SetWrapY(const TextureWrap wrap)
    {
        if (this->wrap_y != wrap) {
            this->wrap_y = wrap;

            this->Bind();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGlWrapValue(wrap));
        }
    }

    void InitTextureGroup()
    {
        texture_group = new TextureGroup();
    }

    void DestroyTextureGroup()
    {
        texture_group = nullptr;
    }

    static Pointer<Texture> GetTexture(const std::string& id)
    {
        auto texture = texture_group->textures.find(id);

        if (texture != texture_group->textures.end()) {
            return texture->second;
        }

        return nullptr;
    }

    void LoadTexture(const std::string& id, const std::string& path)
    {
        if (Assert(GetTexture(id) == nullptr, "LoadTexture: \"" + id + "\" is already loaded")) {
            Pointer<Texture> texture = new Texture(id, path);

            if (texture->texture != 0) {
                texture_group->textures.insert({ id, texture });
            }
        }
    }

    void LoadTexture(const std::string& id, const void* const data, const UIVector2& size, const uint bpp)
    {
        if (Assert(GetTexture(id) == nullptr, "LoadTexture: \"" + id + "\" is already loaded")) {
            Pointer<Texture> texture = new Texture(id, data, size, bpp);
            texture_group->textures.insert({ id, texture });
        }
    }

    void DestroyTexture(const std::string& id)
    {
        if (Assert(GetTexture(id) != nullptr, "DestroyTexture: \"" + id + "\" doesn't exist")) {
            texture_group->textures.erase(id);
        }
    }

    void DestroyAllTextures()
    {
        texture_group->textures.clear();
    }

    void BindTexture(const std::string& id)
    {
        const Pointer<Texture>& texture = GetTexture(id);

        if (Assert(texture != nullptr, "BindTexture: \"" + id + "\" doesn't exist")) {
            texture->Bind();
        }
    }

    uint GetTextureWidth(const std::string& id)
    {
        const Pointer<Texture>& texture = GetTexture(id);

        if (!Assert(texture != nullptr, "GetTextureWidth: \"" + id + "\" doesn't exist")) {
            return 0;
        }

        return texture->size.X();
    }

    uint GetTextureHeight(const std::string& id)
    {
        const Pointer<Texture>& texture = GetTexture(id);

        if (!Assert(texture != nullptr, "GetTextureHeight: \"" + id + "\" doesn't exist")) {
            return 0;
        }

        return texture->size.Y();
    }

    UIVector2 GetTextureSize(const std::string& id)
    {
        const Pointer<Texture>& texture = GetTexture(id);

        if (!Assert(texture != nullptr, "GetTextureSize: \"" + id + "\" doesn't exist")) {
            return 0;
        }

        return texture->size;
    }

    TextureFilter GetTextureFilter(const std::string& id)
    {
        const Pointer<Texture>& texture = GetTexture(id);

        if (!Assert(texture != nullptr, "GetTextureFilter: \"" + id + "\" doesn't exist")) {
            return TextureFilter::Nearest;
        }

        return texture->filter;
    }
    
    void SetTextureFilter(const std::string& id, const TextureFilter filter)
    {
        const Pointer<Texture>& texture = GetTexture(id);

        if (Assert(texture != nullptr, "SetTextureFilter: \"" + id + "\" doesn't exist")) {
            texture->SetFilter(filter);
        }
    }

    TextureWrap GetTextureWrapX(const std::string& id)
    {
        const Pointer<Texture>& texture = GetTexture(id);

        if (!Assert(texture != nullptr, "GetTextureWrapX: \"" + id + "\" doesn't exist")) {
            return TextureWrap::Repeat;
        }

        return texture->wrap_x;
    }

    TextureWrap GetTextureWrapY(const std::string& id)
    {
        const Pointer<Texture>& texture = GetTexture(id);

        if (!Assert(texture != nullptr, "GetTextureWrapY: \"" + id + "\" doesn't exist")) {
            return TextureWrap::Repeat;
        }

        return texture->wrap_y;
    }
    
    void SetTextureWrapX(const std::string& id, const TextureWrap wrap)
    {
        const Pointer<Texture>& texture = GetTexture(id);

        if (Assert(texture != nullptr, "SetTextureWrapX: \"" + id + "\" doesn't exist")) {
            texture->SetWrapX(wrap);
        }
    }
    
    void SetTextureWrapY(const std::string& id, const TextureWrap wrap)
    {
        const Pointer<Texture>& texture = GetTexture(id);

        if (Assert(texture != nullptr, "SetTextureWrapY: \"" + id + "\" doesn't exist")) {
            texture->SetWrapY(wrap);
        }
    }
}