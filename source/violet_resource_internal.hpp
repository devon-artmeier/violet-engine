#ifndef VIOLET_ENGINE_RESOURCE_INTERNAL_HPP
#define VIOLET_ENGINE_RESOURCE_INTERNAL_HPP

namespace Violet
{
    typedef std::unordered_map<std::string, Pointer<Shader>>      ShaderGroup;
    typedef std::unordered_map<std::string, Pointer<Sound>>       SoundGroup;
    typedef std::unordered_map<std::string, Pointer<SpriteSheet>> SpriteSheetGroup;
    typedef std::unordered_map<std::string, Pointer<Texture>>     TextureGroup;
    typedef std::unordered_map<std::string, Pointer<Font>>        FontGroup;

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
            void                    LoadTexture           (const std::string& id, const void* const data, const int width, const int height, const uint bpp);
            void                    DestroyTexture        (const std::string& id);
            void                    DestroyAllTextures    ();
            Pointer<Font>           GetFont               (const std::string& id) const;
            const FontGroup&        GetAllFonts           () const;
            void                    LoadFont              (const std::string& id, const std::string& path);
            void                    DestroyFont           (const std::string& id);
            void                    DestroyAllFonts       ();

        private:
            ShaderGroup      shaders;
            SoundGroup       sounds;
            SpriteSheetGroup sprite_sheets;
            TextureGroup     textures;
            FontGroup        fonts;
    };

    extern void                    InitResources        ();
    extern void                    CloseResources       ();
    extern Pointer<Shader>         GetShader            (const std::string& id);
    extern const ShaderGroup&      GetAllShaders        ();
    extern void                    LoadShaderInternal   (const std::string& id, const std::string& vertex_code, const std::string& frag_code);
    extern void                    DestroyShaderInternal(const std::string& id);
    extern Pointer<Sound>          GetSound             (const std::string& id);
    extern const SoundGroup&       GetAllSounds         ();
    extern Pointer<SpriteSheet>    GetSpriteSheet       (const std::string& id);
    extern const SpriteSheetGroup& GetAllSpriteSheets   ();
    extern void                    LoadTexture          (const std::string& id, const void* const data, const int width, const int height, const uint bpp);
    extern Pointer<Texture>        GetTexture           (const std::string& id);
    extern const TextureGroup&     GetAllTextures       ();
    extern Pointer<Font>           GetFont              (const std::string& id);
    extern const FontGroup&        GetAllFonts          ();
}

#endif // VIOLET_ENGINE_RESOURCE_INTERNAL_HPP