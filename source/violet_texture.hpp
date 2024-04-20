#ifndef VIOLET_ENGINE_TEXTURE_HPP
#define VIOLET_ENGINE_TEXTURE_HPP

#include <string.h>
#include <unordered_map>
#include "glad/glad.h"

namespace Violet
{
    enum class TextureFilter
    {
        Nearest,
        Bilinear
    };

    enum class TextureWrap
    {
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

            bool          IsLoaded ();
            void          Bind     ();
            int           GetWidth ();
            int           GetHeight();
            TextureFilter GetFilter();
            void          SetFilter(const TextureFilter filter);
            TextureWrap   GetWrapX ();
            TextureWrap   GetWrapY ();
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

    class TextureManager
    {
        public:
            ~TextureManager();

            Texture* GetTexture        (const std::string& id);
            void     AddTexture        (const std::string& id, Texture* texture);
            void     DestroyTexture    (const std::string& id);
            void     DestroyAllTextures();

        private:
            std::unordered_map<std::string, Texture*> textures;
    };

    extern void InitTextureManager ();
    extern void CloseTextureManager();
    extern void LoadTexture        (const std::string& id, const std::string& path);
    extern void DestroyTexture     (const std::string& id);
    extern void BindTexture        (const std::string& id);
    extern void SetTextureFilter   (const std::string& id, const TextureFilter filter);
    extern void SetTextureWrapX    (const std::string& id, const TextureWrap wrap);
    extern void SetTextureWrapY    (const std::string& id, const TextureWrap wrap);
}

#endif // VIOLET_ENGINE_TEXTURE_HPP