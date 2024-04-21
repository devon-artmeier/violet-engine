#ifndef VIOLET_ENGINE_SHADER_INTERNAL_HPP
#define VIOLET_ENGINE_SHADER_INTERNAL_HPP

#include "glad/glad.h"
#include "violet_shader.hpp"
#include "violet_types.hpp"

namespace Violet
{
    class Shader
    {
        public:
            Shader(const std::string& id, const std::string& vertex_code, const std::string& frag_code);
            ~Shader();

            bool        IsLoaded  () const;
            std::string GetId     () const;
            GLuint      GetProgram() const;
            void        Attach    () const;
            GLint       GetUniform(const std::string& name) const;

        private:
            std::string id     { "" };
            GLuint      program{ 0 };
    };

    class ShaderManager
    {
        public:
            ~ShaderManager();

            Shader* GetShader        (const std::string& id) const;
            void    AddShader        (const std::string& id, Shader* shader);
            void    DestroyShader    (const std::string& id);
            void    DestroyAllShaders();

        private:
            std::unordered_map<std::string, Shader*> shaders;
    };

    extern void InitShaderManager   ();
    extern void CloseShaderManager  ();
    extern void AttachShader        (const std::string& id);
    extern void DetachShader        ();
}

#endif // VIOLET_ENGINE_SHADER_INTERNAL_HPP