#include "violet_engine.hpp"
#include "violet_texture.hpp"

namespace Violet
{
    static TextureManager* texture_manager{ nullptr };
    static Texture*        current_texture{ nullptr };

    void InitTextureManager()
    {
        texture_manager = new TextureManager();
    }

    void CloseTextureManager()
    {
        delete texture_manager;
    }

    void LoadTexture(const std::string& id, const std::string& path)
    {
        Texture* texture = new Texture(id, path);
        if (texture->IsLoaded()) { texture_manager->AddTexture(id, texture); return; }
        delete texture;

#ifdef VIOLET_DEBUG
        LogError("Failed to load texture \"" + path + "\" with ID \"" + id + "\"");
#endif
    }

    void DestroyTexture(const std::string& id)
    {
        texture_manager->DestroyTexture(id);
    }
    
    void BindTexture(const std::string& id)
    {
        Texture* texture = texture_manager->GetTexture(id);
        if (texture != nullptr) {
            texture->Bind();
        }
    }
    
    void SetTextureFilter(const std::string& id, const TextureFilter filter)
    {
        Texture* texture = texture_manager->GetTexture(id);
        if (texture != nullptr) {
            texture->SetFilter(filter);
        }
    }
    
    void SetTextureWrapX(const std::string& id, const TextureWrap wrap)
    {
        Texture* texture = texture_manager->GetTexture(id);
        if (texture != nullptr) {
            texture->SetWrapX(wrap);
        }
    }
    
    void SetTextureWrapY(const std::string& id, const TextureWrap wrap)
    {
        Texture* texture = texture_manager->GetTexture(id);
        if (texture != nullptr) {
            texture->SetWrapY(wrap);
        }
    }

    Texture::Texture(const std::string& id, const std::string& path)
    {
#ifdef VIOLET_DEBUG
        LogInfo("Loading texture \"" + path + "\" with ID \"" + id + "\"");
#endif
        this->id = id;
        glGenTextures(1, &this->gl_id);

        if (this->gl_id != 0) {
            this->Bind();
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }

    Texture::~Texture()
    {
        if (current_texture == this) {
            current_texture = nullptr;
        }
        if (this->gl_id != 0) {
#ifdef VIOLET_DEBUG
            LogInfo("Destroying texture \"" + id + "\"");
#endif
            glDeleteTextures(1, &this->gl_id);
        }
    }

    bool Texture::IsLoaded()
    {
        return this->gl_id != 0;
    }

    void Texture::Bind()
    {
        if (current_texture != this) {
            current_texture = this;
            glBindTexture(GL_TEXTURE_2D, this->gl_id);  
        }
    }
    
    TextureFilter Texture::GetFilter()
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

    TextureWrap Texture::GetWrapX()
    {
        return this->wrap_x;
    }
    
    TextureWrap Texture::GetWrapY()
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
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGlWrapValue(wrap));
        }
    }

    TextureManager::~TextureManager()
    {
        this->DestroyAllTextures();
    }

    Texture* TextureManager::GetTexture(const std::string& id)
    {
        auto texture = this->textures.find(id);
        if (texture != this->textures.end()) {
            return texture->second;
        }
        return nullptr;
    }

    void TextureManager::AddTexture(const std::string& id, Texture* texture)
    {
        this->DestroyTexture(id);
        this->textures.insert({id, texture});
    }
    
    void TextureManager::DestroyTexture(const std::string& id)
    {
        Texture* texture = GetTexture(id);
        if (texture != nullptr) {
            delete texture;
            this->textures.erase(id);
        }
    }
    
    void TextureManager::DestroyAllTextures()
    {
        for (auto texture : this->textures) {
            delete texture.second;
        }
        this->textures.clear();
    }
}