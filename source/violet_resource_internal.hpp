#ifndef VIOLET_ENGINE_RESOURCE_INTERNAL_HPP
#define VIOLET_ENGINE_RESOURCE_INTERNAL_HPP

#include "violet_audio_internal.hpp"
#include "violet_resource.hpp"
#include "violet_shader_internal.hpp"
#include "violet_sprite_internal.hpp"
#include "violet_texture_internal.hpp"
#include "violet_types.hpp"

namespace Violet
{
    typedef std::unordered_map<std::string, Pointer<Shader>>      ShaderGroup;
    typedef std::unordered_map<std::string, Pointer<Sound>>       SoundGroup;
    typedef std::unordered_map<std::string, Pointer<SpriteSheet>> SpriteSheetGroup;
    typedef std::unordered_map<std::string, Pointer<Texture>>     TextureGroup;

    class ResourceManager
    {
        public:
            Pointer<Shader>         GetShader             (const std::string& id) const;
            const ShaderGroup&      GetAllShaders         () const;
            void                    LoadShader            (const std::string& id, const std::string& vertex_code, const std::string& frag_code);
            void                    DestroyShader         (const std::string& id);
            void                    DestroyAllShaders     ();
            Pointer<Sound>          GetSound              (const std::string& id) const;
            const SoundGroup&       GetAllSounds          () const;
            void                    LoadSound             (const std::string& id, const std::string& path);
            void                    DestroySound          (const std::string& id);
            void                    DestroyAllSounds      ();
            Pointer<SpriteSheet>    GetSpriteSheet        (const std::string& id) const;
            const SpriteSheetGroup& GetAllSpriteSheets    () const;
            void                    LoadSpriteSheet       (const std::string& id, const std::string& path, const std::string& texture);
            void                    DestroySpriteSheet    (const std::string& id);
            void                    DestroyAllSpriteSheets();
            Pointer<Texture>        GetTexture            (const std::string& id) const;
            const TextureGroup&     GetAllTextures        () const;
            void                    LoadTexture           (const std::string& id, const std::string& path);
            void                    DestroyTexture        (const std::string& id);
            void                    DestroyAllTextures    ();

        private:
            ShaderGroup      shaders;
            SoundGroup       sounds;
            SpriteSheetGroup sprite_sheets;
            TextureGroup     textures;
    };

    extern void                    InitResources         ();
    extern void                    CloseResources        ();
    extern Pointer<Shader>         GetShader             (const std::string& id);
    extern const ShaderGroup&      GetAllShaders         ();
    extern Pointer<Sound>          GetSound              (const std::string& id);
    extern const SoundGroup&       GetAllSounds          ();
    extern Pointer<SpriteSheet>    GetSpriteSheet        (const std::string& id);
    extern const SpriteSheetGroup& GetAllSpriteSheets    ();
    extern Pointer<Texture>        GetTexture            (const std::string& id);
    extern const TextureGroup&     GetAllTextures        ();
}

#endif // VIOLET_ENGINE_RESOURCE_INTERNAL_HPP