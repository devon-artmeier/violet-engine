#ifndef VIOLET_ENGINE_SHADER_INTERNAL_HPP
#define VIOLET_ENGINE_SHADER_INTERNAL_HPP

namespace Violet
{
    class Shader
    {
        public:
            Shader(const std::string& id, const std::string& vertex_code, const std::string& frag_code);
            ~Shader();

            void Attach() const;

            std::string id     { "" };
            GLuint      program{ 0 };
    };

    extern void InitShaderGroup   ();
    extern void DestroyShaderGroup();
    extern void AttachShader      (const std::string& id);
    extern void DetachShader      ();
    extern void SetShaderTexture  (const Pointer<Texture>& texture, const uint slot);
}

#endif // VIOLET_ENGINE_SHADER_INTERNAL_HPP