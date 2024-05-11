#ifndef VIOLET_ENGINE_TEXTURE_INTERNAL_HPP
#define VIOLET_ENGINE_TEXTURE_INTERNAL_HPP

namespace Violet
{
    class Texture
    {
        public:
            Texture(const std::string& id, const std::string& path);
            Texture(const std::string& id, const void* const data, const UIVector2& size, const uint bpp);
            ~Texture();

            void Bind        ();
            void UpdatePixels(const void* const data, const UIVector2& size, const uint bpp, const int x, const int y);
            void SetFilter   (const TextureFilter filter);
            void SetWrapX    (const TextureWrap wrap);
            void SetWrapY    (const TextureWrap wrap);

            std::string   id     { "" };
            GLuint        texture{ 0 };
            UIVector2     size   { 0 };
            TextureFilter filter { TextureFilter::Nearest };
            TextureWrap   wrap_x { TextureWrap::Repeat };
            TextureWrap   wrap_y { TextureWrap::Repeat };
    };
    
    extern void InitTextureGroup   ();
    extern void DestroyTextureGroup();
    extern void LoadTexture        (const std::string& id, const void* const data, const UIVector2& size, const uint bpp);
    extern void BindTexture        (const std::string& id);
}

#endif // VIOLET_ENGINE_TEXTURE_INTERNAL_HPP