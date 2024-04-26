#include "violet_message_internal.hpp"
#include "violet_texture_internal.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Violet
{
    static Pointer<ResourceGroup<Texture>> texture_group  { nullptr };
    static GLuint                          current_texture{ 0 };

    void InitTextureGroup()
    {
        texture_group = new ResourceGroup<Texture>();
    }

    void CloseTextureGroup()
    {
        texture_group = nullptr;
    }

    void LoadTexture(const std::string& id, const std::string& path)
    {
        Pointer<Texture> texture(new Texture(id, path));
        if (texture->IsLoaded()) {
            texture_group->Add(id, texture);
        }
    }

    void DestroyTexture(const std::string& id)
    {
        texture_group->Destroy(id);
    }
    
    void BindTexture(const std::string& id)
    {
        const Pointer<Texture>& texture = texture_group->Get(id);
        if (texture != nullptr) texture->Bind();
    }

    int GetTextureWidth(const std::string& id)
    {
        const Pointer<Texture>& texture = texture_group->Get(id);
        if (texture != nullptr) {
            return texture->GetWidth();
        }
        return 0;
    }

    int GetTextureHeight(const std::string& id)
    {
        const Pointer<Texture>& texture = texture_group->Get(id);
        if (texture != nullptr) {
            return texture->GetHeight();
        }
        return 0;
    }

    TextureFilter GetTextureFilter(const std::string& id)
    {
        const Pointer<Texture>& texture = texture_group->Get(id);
        if (texture != nullptr) {
            return texture->GetFilter();
        }
        return TextureFilter::Nearest;
    }
    
    void SetTextureFilter(const std::string& id, const TextureFilter filter)
    {
        const Pointer<Texture>& texture = texture_group->Get(id);
        if (texture != nullptr) {
            texture->SetFilter(filter);
        }
    }

    TextureWrap GetTextureWrapX(const std::string& id)
    {
        const Pointer<Texture>& texture = texture_group->Get(id);
        if (texture != nullptr) {
            return texture->GetWrapX();
        }
        return TextureWrap::Repeat;
    }

    TextureWrap GetTextureWrapY(const std::string& id)
    {
        const Pointer<Texture>& texture = texture_group->Get(id);
        if (texture != nullptr) {
            return texture->GetWrapY();
        }
        return TextureWrap::Repeat;
    }
    
    void SetTextureWrapX(const std::string& id, const TextureWrap wrap)
    {
        const Pointer<Texture>& texture = texture_group->Get(id);
        if (texture != nullptr) {
            texture->SetWrapX(wrap);
        }
    }
    
    void SetTextureWrapY(const std::string& id, const TextureWrap wrap)
    {
        const Pointer<Texture>& texture = texture_group->Get(id);
        if (texture != nullptr) {
            texture->SetWrapY(wrap);
        }
    }

    Texture::Texture(const std::string& id, const std::string& path) : Resource(id)
    {
        uchar* data = stbi_load(path.c_str(), &this->width, &this->height, nullptr, 4);
        this->Info("Loading \"" + path + "\"");

        if (data == nullptr) {
            if (stbi_failure_reason() != nullptr) {
                this->Error("Failed to load");
            } else {
                this->Error((std::string)"Failed to load:\n", data);
            }
            return;
        }

        glGenTextures(1, &this->gl_id);
        this->Bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

        loaded = true;
        this->Info("Loaded successfully");
    }

    Texture::~Texture()
    {
        if (this->loaded) {
            if (current_texture == this->gl_id) {
                current_texture = 0;
            }
            glDeleteTextures(1, &this->gl_id);
        }
    }

    void Texture::Bind() const
    {
        if (current_texture != this->gl_id) {
            current_texture = this->gl_id;
            glBindTexture(GL_TEXTURE_2D, this->gl_id);  
        }
    }
    
    int Texture::GetWidth() const
    {
        return this->width;
    }
    
    int Texture::GetHeight() const
    {
        return this->height;
    }

    TextureFilter Texture::GetFilter() const
    {
        return this->filter;
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

    TextureWrap Texture::GetWrapX() const
    {
        return this->wrap_x;
    }
    
    TextureWrap Texture::GetWrapY() const
    {
        return this->wrap_y;
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
}