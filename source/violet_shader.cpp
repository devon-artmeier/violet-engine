#include "violet_message.hpp"
#include "violet_shader.hpp"
#include "violet_texture.hpp"

namespace Violet
{
    static ShaderManager* shader_manager{ nullptr };
    static const Shader*  current_shader{ nullptr };

    void InitShaderManager()
    {
        shader_manager = new ShaderManager();
    }

    void CloseShaderManager()
    {
        delete shader_manager;
    }

    void LoadShader(const std::string& id, const std::string& vertex_code, const std::string& frag_code)
    {
        Shader* shader = new Shader(id, vertex_code, frag_code);
        if (shader->IsLoaded()) { shader_manager->AddShader(id, shader); return; }
        delete shader;
    }

    void DestroyShader(const std::string& id)
    {
        shader_manager->DestroyShader(id);
    }

    void UseShader(const std::string& id)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->Use();
    }

    void SetShaderFloat(const std::string& id, const std::string& name, const GLfloat value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetFloat(name, value);
    }
    
    void SetShaderInt(const std::string& id, const std::string& name, const GLint value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetInt(name, value);
    }
    
    void SetShaderUInt(const std::string& id, const std::string& name, const GLuint value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetUInt(name, value);
    }
    
    void SetShaderVec2(const std::string& id, const std::string& name, const GLfloat value[2])
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetVec2(name, value);
    }
    
    void SetShaderIVec2(const std::string& id, const std::string& name, const GLint value[2])
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetIVec2(name, value);
    }
    
    void SetShaderUIVec2(const std::string& id, const std::string& name, const GLuint value[2])
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetUIVec2(name, value);
    }
    
    void SetShaderVec3(const std::string& id, const std::string& name, const GLfloat value[3])
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetVec3(name, value);
    }
    
    void SetShaderIVec3(const std::string& id, const std::string& name, const GLint value[3])
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetIVec3(name, value);
    }
    
    void SetShaderUIVec3(const std::string& id, const std::string& name, const GLuint value[3])
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetUIVec3(name, value);
    }
    
    void SetShaderVec4(const std::string& id, const std::string& name, const GLfloat value[4])
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetVec4(name, value);
    }
    
    void SetShaderIVec4(const std::string& id, const std::string& name, const GLint value[4])
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetIVec4(name, value);
    }
    
    void SetShaderUIVec4(const std::string& id, const std::string& name, const GLuint value[4])
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetUIVec4(name, value);
    }
    
    void SetShaderFloatArray(const std::string& id, const std::string& name, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetFloatArray(name, count, value);
    }
    
    void SetShaderIntArray(const std::string& id, const std::string& name, const GLsizei count, const GLint* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetIntArray(name, count, value);
    }
    
    void SetShaderUIntArray(const std::string& id, const std::string& name, const GLsizei count, const GLuint* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetUIntArray(name, count, value);
    }
    
    void SetShaderVec2Array(const std::string& id, const std::string& name, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetVec2Array(name, count, value);
    }
    
    void SetShaderIVec2Array(const std::string& id, const std::string& name, const GLsizei count, const GLint* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetIVec2Array(name, count, value);
    }
    
    void SetShaderUIVec2Array(const std::string& id, const std::string& name, const GLsizei count, const GLuint* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetUIVec2Array(name, count, value);
    }
    
    void SetShaderVec3Array(const std::string& id, const std::string& name, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetVec3Array(name, count, value);
    }
    
    void SetShaderIVec3Array(const std::string& id, const std::string& name, const GLsizei count, const GLint* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetIVec3Array(name, count, value);
    }
    
    void SetShaderUIVec3Array(const std::string& id, const std::string& name, const GLsizei count, const GLuint* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetUIVec3Array(name, count, value);
    }
    
    void SetShaderVec4Array(const std::string& id, const std::string& name, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetVec4Array(name, count, value);
    }
    
    void SetShaderIVec4Array(const std::string& id, const std::string& name, const GLsizei count, const GLint* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetIVec4Array(name, count, value);
    }
    
    void SetShaderUIVec4Array(const std::string& id, const std::string& name, const GLsizei count, const GLuint* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetUIVec4Array(name, count, value);
    }
    
    void SetShaderMatrix2x2(const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetMatrix2x2(name, swap, count, value);
    }
    
    void SetShaderMatrix3x3(const std::string& id, const std::string& name, const bool swap, const GLsizei count,  const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetMatrix3x3(name, swap, count, value);
    }
    
    void SetShaderMatrix4x4(const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetMatrix4x4(name, swap, count, value);
    }
    
    void SetShaderMatrix2x3(const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetMatrix2x3(name, swap, count, value);
    }
    
    void SetShaderMatrix3x2(const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetMatrix3x2(name, swap, count, value);
    }
    
    void SetShaderMatrix2x4(const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetMatrix2x4(name, swap, count, value);
    }
    
    void SetShaderMatrix4x2(const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetMatrix4x2(name, swap, count, value);
    }
    
    void SetShaderMatrix3x4(const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetMatrix3x4(name, swap, count, value);
    }
    
    void SetShaderMatrix4x3(const std::string& id, const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetMatrix4x3(name, swap, count, value);
    }

    void SetShaderTexture(const std::string& id, const std::string& name, const std::string& texture, const unsigned int slot)
    {
        Shader* shader = shader_manager->GetShader(id);
        if (shader != nullptr) shader->SetTexture(name, texture, slot);
    }

    Shader::Shader(const std::string& id, const std::string& vertex_code, const std::string& frag_code)
    {
        char        log[512];
        int         success;
        const char* vertex_code_c = vertex_code.c_str();
        const char* frag_code_c   = frag_code.c_str();

        this->id = id;

        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_code_c, nullptr);
        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (success == 0) {
#ifdef VIOLET_DEBUG
            glGetShaderInfoLog(vertex_shader, 512, nullptr, log);
            LogInfo("Failed to compile vertex shader code for shader program \"" + id + "\":\n" + log);
#endif
            return;
        }
#ifdef VIOLET_DEBUG
        LogInfo("Compiled vertex shader code for shader program \"" + id + "\"");
#endif

        GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag_shader, 1, &frag_code_c, nullptr);
        glCompileShader(frag_shader);
        glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
        if (success == 0) {
#ifdef VIOLET_DEBUG
            glGetShaderInfoLog(frag_shader, 512, nullptr, log);
            LogInfo("Failed to compile fragment shader code for shader program \"" + id + "\":\n" + log);
#endif 
            glDeleteShader(vertex_shader);
            return;
        }
#ifdef VIOLET_DEBUG
        LogInfo("Compiled fragment shader code for shader program \"" + id + "\"");
#endif

#ifdef VIOLET_DEBUG
#endif
        this->gl_id = glCreateProgram();
        glAttachShader(this->gl_id, vertex_shader);
        glAttachShader(this->gl_id, frag_shader);
        glLinkProgram(this->gl_id);
        glGetProgramiv(this->gl_id, GL_LINK_STATUS, &success);
        if (success == 0) {
#ifdef VIOLET_DEBUG
            glGetProgramInfoLog(this->gl_id, 512, nullptr, log);
            LogInfo("Failed to link code for shader program \"" + id + "\":\n" + log);
#endif
        } else {
            this->loaded = true;
#ifdef VIOLET_DEBUG
            LogInfo("Linked code for shader program \"" + id + "\"");
#endif
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(frag_shader);
    }

    Shader::~Shader()
    {
        if (current_shader == this) {
            current_shader = nullptr;
        }
        if (this->loaded) {
            glDeleteProgram(this->gl_id);
#ifdef VIOLET_DEBUG
            LogInfo("Destroyed shader program \"" + this->id + "\"");
#endif
        }
    }

    bool Shader::IsLoaded() const
    {
        return this->loaded;
    }

    void Shader::Use() const
    {
        if (current_shader != this) {
            current_shader = this;
            glUseProgram(this->gl_id);
        }
    }

    void Shader::SetFloat(const std::string& name, const GLfloat value) const
    {
        this->Use();
        glUniform1f(this->GetUniformLocation(name), value);
    }

    void Shader::SetInt(const std::string& name, const GLint value) const
    {
        this->Use();
        glUniform1i(this->GetUniformLocation(name), value);
    }

    void Shader::SetUInt(const std::string& name, const GLuint value) const
    {
        this->Use();
        glUniform1ui(this->GetUniformLocation(name), value);
    }

    void Shader::SetVec2(const std::string& name, const GLfloat value[2]) const
    {
        this->Use();
        glUniform2f(this->GetUniformLocation(name), value[0], value[1]);
    }

    void Shader::SetIVec2(const std::string& name, const GLint value[2]) const
    {
        this->Use();
        glUniform2i(this->GetUniformLocation(name), value[0], value[1]);
    }

    void Shader::SetUIVec2(const std::string& name, const GLuint value[2]) const
    {
        this->Use();
        glUniform2ui(this->GetUniformLocation(name), value[0], value[1]);
    }

    void Shader::SetVec3(const std::string& name, const GLfloat value[3]) const
    {
        this->Use();
        glUniform3f(this->GetUniformLocation(name), value[0], value[1], value[2]);
    }

    void Shader::SetIVec3(const std::string& name, const GLint value[3]) const
    {
        this->Use();
        glUniform3i(this->GetUniformLocation(name), value[0], value[1], value[2]);
    }

    void Shader::SetUIVec3(const std::string& name, const GLuint value[3]) const
    {
        this->Use();
        glUniform3ui(this->GetUniformLocation(name), value[0], value[1], value[2]);
    }

    void Shader::SetVec4(const std::string& name, const GLfloat value[4]) const
    {
        this->Use();
        glUniform4f(this->GetUniformLocation(name), value[0], value[1], value[2], value[3]);
    }

    void Shader::SetIVec4(const std::string& name, const GLint value[4]) const
    {
        this->Use();
        glUniform4i(this->GetUniformLocation(name), value[0], value[1], value[2], value[3]);
    }

    void Shader::SetUIVec4(const std::string& name, const GLuint value[4]) const
    {
        this->Use();
        glUniform4ui(this->GetUniformLocation(name), value[0], value[1], value[2], value[3]);
    }

    void Shader::SetFloatArray(const std::string& name, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniform1fv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetIntArray(const std::string& name, const GLsizei count, const GLint* const value) const
    {
        this->Use();
        glUniform1iv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetUIntArray(const std::string& name, const GLsizei count, const GLuint* const value) const
    {
        this->Use();
        glUniform1uiv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetVec2Array(const std::string& name, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniform2fv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetIVec2Array(const std::string& name, const GLsizei count, const GLint* const value) const
    {
        this->Use();
        glUniform2iv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetUIVec2Array(const std::string& name, const GLsizei count, const GLuint* const value) const
    {
        this->Use();
        glUniform2uiv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetVec3Array(const std::string& name, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniform3fv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetIVec3Array(const std::string& name, const GLsizei count, const GLint* const value) const
    {
        this->Use();
        glUniform3iv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetUIVec3Array(const std::string& name, const GLsizei count, const GLuint* const value) const
    {
        this->Use();
        glUniform3uiv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetVec4Array(const std::string& name, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniform4fv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetIVec4Array(const std::string& name, const GLsizei count, const GLint* const value) const
    {
        this->Use();
        glUniform4iv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetUIVec4Array(const std::string& name, const GLsizei count, const GLuint* const value) const
    {
        this->Use();
        glUniform4uiv(this->GetUniformLocation(name), count, value);
    }

    void Shader::SetMatrix2x2(const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniformMatrix2fv(this->GetUniformLocation(name), count, swap, value);
    }

    void Shader::SetMatrix3x3(const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniformMatrix3fv(this->GetUniformLocation(name), count, swap, value);
    }

    void Shader::SetMatrix4x4(const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniformMatrix4fv(this->GetUniformLocation(name), count, swap, value);
    }

    void Shader::SetMatrix2x3(const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniformMatrix2x3fv(this->GetUniformLocation(name), count, swap, value);
    }

    void Shader::SetMatrix3x2(const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniformMatrix3x2fv(this->GetUniformLocation(name), count, swap, value);
    }

    void Shader::SetMatrix2x4(const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniformMatrix2x4fv(this->GetUniformLocation(name), count, swap, value);
    }

    void Shader::SetMatrix4x2(const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniformMatrix4x2fv(this->GetUniformLocation(name), count, swap, value);
    }

    void Shader::SetMatrix3x4(const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniformMatrix3x4fv(this->GetUniformLocation(name), count, swap, value);
    }

    void Shader::SetMatrix4x3(const std::string& name, const bool swap, const GLsizei count, const GLfloat* const value) const
    {
        this->Use();
        glUniformMatrix4x3fv(this->GetUniformLocation(name), count, swap, value);
    }

    void Shader::SetTexture(const std::string& name, const std::string& texture, const unsigned int slot)
    {
        this->Use();
        glActiveTexture(GL_TEXTURE0 + slot);
        BindTexture(texture);
    }

    GLint Shader::GetUniformLocation(const std::string& name) const
    {
        return glGetUniformLocation(this->gl_id, name.c_str());
    }
    
    ShaderManager::~ShaderManager()
    {
        this->DestroyAllShaders();
    }

    Shader* ShaderManager::GetShader(const std::string& id) const
    {
        auto shader = this->shaders.find(id);
        if (shader != this->shaders.end()) {
            return shader->second;
        }
        return nullptr;
    }

    void ShaderManager::AddShader(const std::string& id, Shader* shader)
    {
        this->DestroyShader(id);
        this->shaders.insert({id, shader});
    }
    
    void ShaderManager::DestroyShader(const std::string& id)
    {
        Shader* shader = GetShader(id);
        if (shader != nullptr) {
            delete shader;
            this->shaders.erase(id);
        }
    }
    
    void ShaderManager::DestroyAllShaders()
    {
        for (auto shader : this->shaders) {
            delete shader.second;
        }
        this->shaders.clear();
    }
}