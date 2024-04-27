#ifndef VIOLET_ENGINE_SHADER_INTERNAL_HPP
#define VIOLET_ENGINE_SHADER_INTERNAL_HPP

#include <glad.h>
#include "violet_shader.hpp"

namespace Violet
{
    class Shader
    {
        public:
            Shader(const std::string& id, const std::string& vertex_code, const std::string& frag_code);
            ~Shader();

            bool   IsLoaded  () const;
            GLuint GetProgram() const;
            void   Attach    () const;
            GLint  GetUniform(const std::string& name) const;

        private:
            std::string id     { "" };
            bool        loaded { false };
            GLuint      program{ 0 };
    };

    extern void InitShaders ();
    extern void AttachShader(const std::string& id);
    extern void DetachShader();
}

#endif // VIOLET_ENGINE_SHADER_INTERNAL_HPP