#include "violet_engine_internal.hpp"

namespace Violet
{
    static Pointer<ResourceManager> resource_manager{ nullptr };

    static const char* reserved_shaders[] = {
        "shader_sprite_internal"
    };

    static bool IsShaderReserved(const std::string& id)
    {
        for (int i = 0; i < sizeof(reserved_shaders) / sizeof(const char*); i++) {
            if (id.compare(reserved_shaders[i]) == 0) {
#ifdef VIOLET_DEBUG
                LogError("\"" + id + "\" is a reserved shader name");
#endif
                return true;
            }
        }
        return false;
    }

    Pointer<Shader> ResourceManager::GetShader(const std::string& id) const
    {
        auto shader = this->shaders.find(id);
        if (shader != this->shaders.end()) {
            return shader->second;
        }
        return Pointer<Shader>(nullptr);
    }

    const ShaderGroup& ResourceManager::GetAllShaders() const
    {
        return this->shaders;
    }

    void ResourceManager::LoadShader(const std::string& id, const std::string& vertex_code, const std::string& frag_code)
    {
        if (this->GetShader(id) == nullptr) {
            Pointer<Shader> shader(new Shader(id, vertex_code, frag_code));
            if (shader->IsLoaded()) {
                this->shaders.insert({ id, shader });
            }
        }
    }

    void ResourceManager::DestroyShader(const std::string& id)
    {
        const Pointer<Shader>& shader = this->GetShader(id);
        if (shader != nullptr) {
            this->shaders.erase(id);
        }
    }

    void ResourceManager::DestroyAllShaders()
    {
        this->shaders.clear();
    }

    Pointer<Sound> ResourceManager::GetSound(const std::string& id) const
    {
        auto sound = this->sounds.find(id);
        if (sound != this->sounds.end()) {
            return sound->second;
        }
        return Pointer<Sound>(nullptr);
    }

    const SoundGroup& ResourceManager::GetAllSounds() const
    {
        return this->sounds;
    }

    void ResourceManager::LoadSound(const std::string& id, const std::string& path)
    {
        if (this->GetSound(id) == nullptr) {
            Pointer<Sound> sound = LoadWavSound(id, path);
            if (sound->IsLoaded()) { this->sounds.insert({ id, sound }); return; }

            sound = LoadMp3Sound(id, path);
            if (sound->IsLoaded()) { this->sounds.insert({ id, sound }); return; }

            sound = LoadOggSound(id, path);
            if (sound->IsLoaded()) { this->sounds.insert({ id, sound }); return; }

            sound = LoadFlacSound(id, path);
            if (sound->IsLoaded()) { this->sounds.insert({ id, sound }); return; }
        }
    }

    void ResourceManager::DestroySound(const std::string& id)
    {
        const Pointer<Sound>& sound = this->GetSound(id);
        if (sound != nullptr) {
            this->sounds.erase(id);
        }
    }

    void ResourceManager::DestroyAllSounds()
    {
        this->sounds.clear();
    }

    Pointer<SpriteSheet> ResourceManager::GetSpriteSheet(const std::string& id) const
    {
        auto sprite_sheet = this->sprite_sheets.find(id);
        if (sprite_sheet != this->sprite_sheets.end()) {
            return sprite_sheet->second;
        }
        return Pointer<SpriteSheet>(nullptr);
    }

    const SpriteSheetGroup& ResourceManager::GetAllSpriteSheets() const
    {
        return this->sprite_sheets;
    }

    void ResourceManager::LoadSpriteSheet(const std::string& id, const std::string& path, const std::string& texture)
    {
        if (this->GetSpriteSheet(id) == nullptr) {
            Pointer<SpriteSheet> sprite_sheet(new SpriteSheet(id, path, texture));
            if (sprite_sheet->IsLoaded()) {
                this->sprite_sheets.insert({ id, sprite_sheet });
            }
        }
    }

    void ResourceManager::DestroySpriteSheet(const std::string& id)
    {
        const Pointer<SpriteSheet>& sprite_sheet = this->GetSpriteSheet(id);
        if (sprite_sheet != nullptr) {
            this->sprite_sheets.erase(id);
        }
    }

    void ResourceManager::DestroyAllSpriteSheets()
    {
        this->sprite_sheets.clear();
    }

    Pointer<Texture> ResourceManager::GetTexture(const std::string& id) const
    {
        auto texture = this->textures.find(id);
        if (texture != this->textures.end()) {
            return texture->second;
        }
        return Pointer<Texture>(nullptr);
    }

    const TextureGroup& ResourceManager::GetAllTextures() const
    {
        return this->textures;
    }

    void ResourceManager::LoadTexture(const std::string& id, const std::string& path)
    {
        if (this->GetTexture(id) == nullptr) {
            Pointer<Texture> texture(new Texture(id, path));
            if (texture->IsLoaded()) {
                this->textures.insert({ id, texture });
            }
        }
    }

    void ResourceManager::DestroyTexture(const std::string& id)
    {
        const Pointer<Texture>& texture = this->GetTexture(id);
        if (texture != nullptr) {
            this->textures.erase(id);
        }
    }

    void ResourceManager::DestroyAllTextures()
    {
        this->textures.clear();
    }

    extern void InitResources()
    {
        resource_manager = new ResourceManager();
    }

    extern void CloseResources()
    {
        resource_manager = nullptr;
    }

    Pointer<Shader> GetShader(const std::string& id)
    {
        return resource_manager->GetShader(id);
    }

    const ShaderGroup& GetAllShaders()
    {
        return resource_manager->GetAllShaders();
    }

    void LoadShader(const std::string& id, const std::string& vertex_code, const std::string& frag_code)
    {
        if (!IsShaderReserved(id)) {
            LoadShaderInternal(id, vertex_code, frag_code);
        }
    }

    void LoadShaderInternal(const std::string& id, const std::string& vertex_code, const std::string& frag_code)
    {
        resource_manager->LoadShader(id, vertex_code, frag_code);
    }

    void DestroyShader(const std::string& id)
    {
        if (!IsShaderReserved(id)) {
            DestroyShaderInternal(id);
        }
    }

    void DestroyShaderInternal(const std::string& id)
    {
        resource_manager->DestroyShader(id);
    }

    void DestroyAllShaders()
    {
        resource_manager->DestroyAllShaders();
    }

    Pointer<Sound> GetSound(const std::string& id)
    {
        return resource_manager->GetSound(id);
    }

    const SoundGroup& GetAllSounds()
    {
        return resource_manager->GetAllSounds();
    }

    void LoadSound(const std::string& id, const std::string& path)
    {
        resource_manager->LoadSound(id, path);
    }

    void DestroySound(const std::string& id)
    {
        resource_manager->DestroySound(id);
    }

    void DestroyAllSounds()
    {
        resource_manager->DestroyAllSounds();
    }

    Pointer<SpriteSheet> GetSpriteSheet(const std::string& id)
    {
        return resource_manager->GetSpriteSheet(id);
    }

    const SpriteSheetGroup& GetAllSpriteSheets()
    {
        return resource_manager->GetAllSpriteSheets();
    }

    void LoadSpriteSheet(const std::string& id, const std::string& path, const std::string& texture)
    {
        resource_manager->LoadSpriteSheet(id, path, texture);
    }

    void DestroySpriteSheet(const std::string& id)
    {
        resource_manager->DestroySpriteSheet(id);
    }

    void DestroyAllSpriteSheets()
    {
        resource_manager->DestroyAllSpriteSheets();
    }

    Pointer<Texture> GetTexture(const std::string& id)
    {
        return resource_manager->GetTexture(id);
    }

    const TextureGroup& GetAllTextures()
    {
        return resource_manager->GetAllTextures();
    }

    void LoadTexture(const std::string& id, const std::string& path)
    {
        resource_manager->LoadTexture(id, path);
    }

    void DestroyTexture(const std::string& id)
    {
        resource_manager->DestroyTexture(id);
    }

    void DestroyAllTextures()
    {
        resource_manager->DestroyAllTextures();
    }
}