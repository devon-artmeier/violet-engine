#ifndef VIOLET_ENGINE_SHADER_INTERNAL_HPP
#define VIOLET_ENGINE_SHADER_INTERNAL_HPP

#include <glad.h>
#include "violet_resource.hpp"
#include "violet_shader.hpp"

namespace Violet
{
    class Shader : public Resource
    {
        public:
            Shader(const std::string& id, const std::string& vertex_code, const std::string& frag_code);
            ~Shader();

            GLuint GetProgram() const;
            void   Attach    () const;
            GLint  GetUniform(const std::string& name) const;

        private:
            GLuint program{ 0 };
    };

    extern void InitShaders          ();
    extern void CloseShaders         ();
    extern void LoadShaderInternal   (const std::string& id, const std::string& vertex_code, const std::string& frag_code);
    extern void DestroyShaderInternal(const std::string& id);
    extern void AttachShader         (const std::string& id);
    extern void DetachShader         ();
}

#endif // VIOLET_ENGINE_SHADER_INTERNAL_HPP