#ifndef VIOLET_ENGINE_SHADER_HPP
#define VIOLET_ENGINE_SHADER_HPP

#include <string>
#include <unordered_map>
#include "glad/glad.h"

namespace Violet
{
    class Shader
    {
        public:
            Shader(const std::string& id, const std::string& vertex_code, const std::string& frag_code);
            ~Shader();

            bool IsLoaded      () const;
            void Use           () const;
            void SetFloat      (const std::string& name, const GLfloat value) const;
            void SetInt        (const std::string& name, const GLint value) const;
            void SetUInt       (const std::string& name, const GLuint value) const;
            void SetVec2       (const std::string& name, const GLfloat value[2]) const;
            void SetIVec2      (const std::string& name, const GLint value[2]) const;
            void SetUIVec2     (const std::string& name, const GLuint value[2]) const;
            void SetVec3       (const std::string& name, const GLfloat value[3]) const;
            void SetIVec3      (const std::string& name, const GLint value[3]) const;
            void SetUIVec3     (const std::string& name, const GLuint value[3]) const;
            void SetVec4       (const std::string& name, const GLfloat value[4]) const;
            void SetIVec4      (const std::string& name, const GLint value[4]) const;
            void SetUIVec4     (const std::string& name, const GLuint value[4]) const;
            void SetFloatArray (const std::string& name, const GLsizei count, const GLfloat* const value) const;
            void SetIntArray   (const std::string& name, const GLsizei count, const GLint* const value) const;
            void SetUIntArray  (const std::string& name, const GLsizei count, const GLuint* const value) const;
            void SetVec2Array  (const std::string& name, const GLsizei count, const GLfloat* const value) const;
            void SetIVec2Array (const std::string& name, const GLsizei count, const GLint* const value) const;
            void SetUIVec2Array(const std::string& name, const GLsizei count, const GLuint* const value) const;
            void SetVec3Array  (const std::string& name, const GLsizei count, const GLfloat* const value) const;
            void SetIVec3Array (const std::string& name, const GLsizei count, const GLint* const value) const;
            void SetUIVec3Array(const std::string& name, const GLsizei count, const GLuint* const value) const;
            void SetVec4Array  (const std::string& name, const GLsizei count, const GLfloat* const value) const;
            void SetIVec4Array (const std::string& name, const GLsizei count, const GLint* const value) const;
            void SetUIVec4Array(const std::string& name, const GLsizei count, const GLuint* const value) const;
            void SetMatrix2x2  (const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const;
            void SetMatrix3x3  (const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const;
            void SetMatrix4x4  (const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const;
            void SetMatrix2x3  (const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const;
            void SetMatrix3x2  (const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const;
            void SetMatrix2x4  (const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const;
            void SetMatrix4x2  (const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const;
            void SetMatrix3x4  (const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const;
            void SetMatrix4x3  (const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const;
            void SetTexture    (const std::string& name, const std::string& texture, const unsigned int slot);

        private:
            GLint GetUniformLocation(const std::string& name) const;

            std::string id    { "" };
            GLuint      gl_id { 0 };
            bool        loaded{ false };
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
    extern void LoadShader          (const std::string& id, const std::string& vertex_code, const std::string& frag_code);
    extern void DestroyShader       (const std::string& id);
    extern void UseShader           (const std::string& id);
    extern void SetShaderFloat      (const std::string& id, const std::string& name, const GLfloat value);
    extern void SetShaderInt        (const std::string& id, const std::string& name, const GLint value);
    extern void SetShaderUInt       (const std::string& id, const std::string& name, const GLuint value);
    extern void SetShaderVec2       (const std::string& id, const std::string& name, const GLfloat value[2]);
    extern void SetShaderIVec2      (const std::string& id, const std::string& name, const GLint value[2]);
    extern void SetShaderUIVec2     (const std::string& id, const std::string& name, const GLuint value[2]);
    extern void SetShaderVec3       (const std::string& id, const std::string& name, const GLfloat value[3]);
    extern void SetShaderIVec3      (const std::string& id, const std::string& name, const GLint value[3]);
    extern void SetShaderUIVec3     (const std::string& id, const std::string& name, const GLuint value[3]);
    extern void SetShaderVec4       (const std::string& id, const std::string& name, const GLfloat value[4]);
    extern void SetShaderIVec4      (const std::string& id, const std::string& name, const GLint value[4]);
    extern void SetShaderUIVec4     (const std::string& id, const std::string& name, const GLuint value[4]);
    extern void SetShaderFloatArray (const std::string& id, const std::string& name, const GLsizei count, const GLfloat* const value);
    extern void SetShaderIntArray   (const std::string& id, const std::string& name, const GLsizei count, const GLint* const value);
    extern void SetShaderUIntArray  (const std::string& id, const std::string& name, const GLsizei count, const GLuint* const value);
    extern void SetShaderVec2Array  (const std::string& id, const std::string& name, const GLsizei count, const GLfloat* const value);
    extern void SetShaderIVec2Array (const std::string& id, const std::string& name, const GLsizei count, const GLint* const value);
    extern void SetShaderUIVec2Array(const std::string& id, const std::string& name, const GLsizei count, const GLuint* const value);
    extern void SetShaderVec3Array  (const std::string& id, const std::string& name, const GLsizei count, const GLfloat* const value);
    extern void SetShaderIVec3Array (const std::string& id, const std::string& name, const GLsizei count, const GLint* const value);
    extern void SetShaderUIVec3Array(const std::string& id, const std::string& name, const GLsizei count, const GLuint* const value);
    extern void SetShaderVec4Array  (const std::string& id, const std::string& name, const GLsizei count, const GLfloat* const value);
    extern void SetShaderIVec4Array (const std::string& id, const std::string& name, const GLsizei count, const GLint* const value);
    extern void SetShaderUIVec4Array(const std::string& id, const std::string& name, const GLsizei count, const GLuint* const value);
    extern void SetShaderMatrix2x2  (const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value);
    extern void SetShaderMatrix3x3  (const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value);
    extern void SetShaderMatrix4x4  (const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value);
    extern void SetShaderMatrix2x3  (const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value);
    extern void SetShaderMatrix3x2  (const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value);
    extern void SetShaderMatrix2x4  (const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value);
    extern void SetShaderMatrix4x2  (const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value);
    extern void SetShaderMatrix3x4  (const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value);
    extern void SetShaderMatrix4x3  (const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value);
    extern void SetShaderTexture    (const std::string& id, const std::string& name, const std::string& texture, const unsigned int slot);
}

#endif // VIOLET_ENGINE_SHADER_HPP