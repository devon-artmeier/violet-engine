#ifndef VIOLET_ENGINE_TEXTURE_INTERNAL_HPP
#define VIOLET_ENGINE_TEXTURE_INTERNAL_HPP

namespace Violet
{
    class Texture
    {
        public:
            Texture(const std::string& id, const std::string& path);
            Texture(const std::string& id, const void* const data, const int width, const int height, const uint bpp);
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
            bool          loaded{ false };
            GLuint        gl_id { 0 };
            int           width { 0 };
            int           height{ 0 };
            TextureFilter filter{ TextureFilter::Nearest };
            TextureWrap   wrap_x{ TextureWrap::Repeat };
            TextureWrap   wrap_y{ TextureWrap::Repeat };
    };

    extern void BindTexture(const std::string& id);
}

#endif // VIOLET_ENGINE_TEXTURE_INTERNAL_HPP