#ifndef VIOLET_ENGINE_TEXTURE_INTERNAL_HPP
#define VIOLET_ENGINE_TEXTURE_INTERNAL_HPP

#include "glad/glad.h"
#include "violet_texture.hpp"

namespace Violet
{
    enum class TextureFilter {
        Nearest,
        Bilinear
    };

    enum class TextureWrap {
        Repeat,
        Mirror,
        ClampEdge,
        ClampBorder
    };
    
    class Texture
    {
        public:
            Texture(const std::string& id, const std::string& path);
            ~Texture();

            bool          IsLoaded () const;
            void          Bind     () const;
            int           GetWidth () const;
            int           GetHeight() const;
            TextureFilter GetFilter() const;
            void          SetFilter(const TextureFilter filter);
            TextureWrap   GetWrapX () const;
            TextureWrap   GetWrapY () const;
            void          SetWrapX (const TextureWrap wrap);
            void          SetWrapY (const TextureWrap wrap);

        private:
            std::string   id    { "" };
            GLuint        gl_id { 0 };
            bool          loaded{false };
            int           width { 0 };
            int           height{ 0 };
            TextureFilter filter{ TextureFilter::Nearest };
            TextureWrap   wrap_x{ TextureWrap::Repeat };
            TextureWrap   wrap_y{ TextureWrap::Repeat };
    };

    class TextureGroup
    {
        public:
            ~TextureGroup();

            Texture* GetTexture        (const std::string& id) const;
            void     AddTexture        (const std::string& id, Texture* texture);
            void     DestroyTexture    (const std::string& id);
            void     DestroyAllTextures();

        private:
            std::unordered_map<std::string, Texture*> textures;
    };

    extern void          InitTextureGroup ();
    extern void          CloseTextureGroup();
    extern void          BindTexture      (const std::string& id);
    extern int           GetTextureWidth  (const std::string& id);
    extern int           GetTextureHeight (const std::string& id);
    extern TextureFilter GetTextureFilter (const std::string& id);
    extern void          SetTextureFilter (const std::string& id, const TextureFilter filter);
    extern TextureWrap   GetTextureWrapX  (const std::string& id);
    extern TextureWrap   GetTextureWrapY  (const std::string& id);
    extern void          SetTextureWrapX  (const std::string& id, const TextureWrap wrap);
    extern void          SetTextureWrapY  (const std::string& id, const TextureWrap wrap);
}

#endif // VIOLET_ENGINE_TEXTURE_INTERNAL_HPP