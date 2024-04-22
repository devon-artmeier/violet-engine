#include "violet_message_internal.hpp"
#include "violet_texture_internal.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Violet
{
    static TextureGroup*  texture_group  { nullptr };
    static const Texture* current_texture{ nullptr };

    void InitTextureGroup()
    {
        texture_group = new TextureGroup();
    }

    void CloseTextureGroup()
    {
        delete texture_group;
    }

    void LoadTexture(const std::string& id, const std::string& path)
    {
        Texture* texture = new Texture(id, path);
        if (texture->IsLoaded()) { texture_group->AddTexture(id, texture); return; }
        delete texture;
    }

    void DestroyTexture(const std::string& id)
    {
        texture_group->DestroyTexture(id);
    }
    
    void BindTexture(const std::string& id)
    {
        Texture* texture = texture_group->GetTexture(id);
        if (texture != nullptr) texture->Bind();
    }

    int GetTextureWidth(const std::string& id)
    {
        Texture* texture = texture_group->GetTexture(id);
        if (texture != nullptr) texture->GetWidth();
        return 0;
    }

    int GetTextureHeight(const std::string& id)
    {
        Texture* texture = texture_group->GetTexture(id);
        if (texture != nullptr) texture->GetHeight();
        return 0;
    }

    TextureFilter GetTextureFilter(const std::string& id)
    {
        Texture* texture = texture_group->GetTexture(id);
        if (texture != nullptr) texture->GetFilter();
        return TextureFilter::Nearest;
    }
    
    void SetTextureFilter(const std::string& id, const TextureFilter filter)
    {
        Texture* texture = texture_group->GetTexture(id);
        if (texture != nullptr) texture->SetFilter(filter);
    }

    TextureWrap GetTextureWrapX(const std::string& id)
    {
        Texture* texture = texture_group->GetTexture(id);
        if (texture != nullptr) texture->GetWrapX();
        return TextureWrap::Repeat;
    }

    TextureWrap GetTextureWrapY(const std::string& id)
    {
        Texture* texture = texture_group->GetTexture(id);
        if (texture != nullptr) texture->GetWrapY();
        return TextureWrap::Repeat;
    }

    
    void SetTextureWrapX(const std::string& id, const TextureWrap wrap)
    {
        Texture* texture = texture_group->GetTexture(id);
        if (texture != nullptr) texture->SetWrapX(wrap);
    }
    
    void SetTextureWrapY(const std::string& id, const TextureWrap wrap)
    {
        Texture* texture = texture_group->GetTexture(id);
        if (texture != nullptr) texture->SetWrapY(wrap);
    }

    Texture::Texture(const std::string& id, const std::string& path)
    {
        this->id = id;
        stbi_set_flip_vertically_on_load(1);
        uchar *data = stbi_load(path.c_str(), &this->width, &this->height, nullptr, 4);
        
        if (data != nullptr) {
            glGenTextures(1, &this->gl_id);
            
            this->Bind();
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            
            stbi_image_free(data);
            loaded = true;
#ifdef VIOLET_DEBUG
            LogInfo("Loaded texture \"" + id + "\" from \"" + path + "\"");
#endif
        } else {
#ifdef VIOLET_DEBUG
            LogError("Failed to load texture \"" + id + "\" from \"" + path + "\"");
#endif
        }
    }

    Texture::~Texture()
    {
        if (current_texture == this) {
            current_texture = nullptr;
        }
        if (this->loaded) {
            glDeleteTextures(1, &this->gl_id);
#ifdef VIOLET_DEBUG
            LogInfo("Destroyed texture \"" + id + "\"");
#endif
        }
    }

    bool Texture::IsLoaded() const
    {
        return this->loaded;
    }

    void Texture::Bind() const
    {
        if (current_texture != this) {
            current_texture = this;
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

    TextureGroup::~TextureGroup()
    {
        this->DestroyAllTextures();
    }

    Texture* TextureGroup::GetTexture(const std::string& id) const
    {
        auto texture = this->textures.find(id);
        if (texture != this->textures.end()) {
            return texture->second;
        }
        return nullptr;
    }

    void TextureGroup::AddTexture(const std::string& id, Texture* texture)
    {
        this->DestroyTexture(id);
        this->textures.insert({id, texture});
    }
    
    void TextureGroup::DestroyTexture(const std::string& id)
    {
        Texture* texture = GetTexture(id);
        if (texture != nullptr) {
            delete texture;
            this->textures.erase(id);
        }
    }
    
    void TextureGroup::DestroyAllTextures()
    {
        for (auto texture : this->textures) {
            delete texture.second;
        }
        this->textures.clear();
    }
}