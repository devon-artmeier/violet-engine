#include "violet_message_internal.hpp"
#include "violet_shader_internal.hpp"
#include "violet_texture_internal.hpp"

namespace Violet
{
    static ShaderGroup*  shader_group  { nullptr };
    static const Shader* current_shader{ nullptr };

    void InitShaderGroup()
    {
        shader_group = new ShaderGroup();
    }

    void CloseShaderGroup()
    {
        delete shader_group;
    }

    void LoadShader(const std::string& id, const std::string& vertex_code, const std::string& frag_code)
    {
        Shader* shader = new Shader(id, vertex_code, frag_code);
        if (shader->GetProgram() != 0) {
            shader_group->AddShader(id, shader);
        } else {
            delete shader;
        }
    }

    void DestroyShader(const std::string& id)
    {
        shader_group->DestroyShader(id);
    }

    void AttachShader(const std::string& id)
    {
        Shader* shader = shader_group->GetShader(id);
        if (shader != nullptr) {
            shader->Attach();
        }
    }

    void DetachShader()
    {
        current_shader = nullptr;
    }

    static int GetUniformLocation(const std::string& name)
    {
        if (current_shader != nullptr) {
            return current_shader->GetUniform(name);
        }
        return 0;
    }

    void SetShaderFloat(const std::string& name, const float value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderFloat: No shader is attached");
#endif
        } else {
            glUniform1f(GetUniformLocation(name), value);
        }
    }
    
    void SetShaderInt(const std::string& name, const int value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderInt: No shader is attached");
#endif
        } else {
            glUniform1i(GetUniformLocation(name), value);
        }
    }
    
    void SetShaderUInt(const std::string& name, const uint value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderUInt: No shader is attached");
#endif
        } else {
            glUniform1ui(GetUniformLocation(name), value);
        }
    }
    
    void SetShaderVec2(const std::string& name, const float value[2])
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderVec2: No shader is attached");
#endif
        } else {
            glUniform2f(GetUniformLocation(name), value[0], value[1]);
        }
    }
    
    void SetShaderIVec2(const std::string& name, const int value[2])
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderIVec2: No shader is attached");
#endif
        } else {
            glUniform2i(GetUniformLocation(name), value[0], value[1]);
        }
    }
    
    void SetShaderUIVec2(const std::string& name, const uint value[2])
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderUIVec2: No shader is attached");
#endif
        } else {
            glUniform2ui(GetUniformLocation(name), value[0], value[1]);
        }
    }
    
    void SetShaderVec3(const std::string& name, const float value[3])
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderVec3: No shader is attached");
#endif
        } else {
            glUniform3f(GetUniformLocation(name), value[0], value[1], value[2]);
        }
    }
    
    void SetShaderIVec3(const std::string& name, const int value[3])
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderIVec3: No shader is attached");
#endif
        } else {
            glUniform3i(GetUniformLocation(name), value[0], value[1], value[2]);
        }
    }
    
    void SetShaderUIVec3(const std::string& name, const uint value[3])
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderUIVec3: No shader is attached");
#endif
        } else {
            glUniform3ui(GetUniformLocation(name), value[0], value[1], value[2]);
        }
    }
    
    void SetShaderVec4(const std::string& name, const float value[4])
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderVec4: No shader is attached");
#endif
        } else {
            glUniform4f(GetUniformLocation(name), value[0], value[1], value[2], value[3]);
        }
    }
    
    void SetShaderIVec4(const std::string& name, const int value[4])
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderIVec4: No shader is attached");
#endif
        } else {
            glUniform4i(GetUniformLocation(name), value[0], value[1], value[2], value[3]);
        }
    }
    
    void SetShaderUIVec4(const std::string& name, const uint value[4])
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderUIVec4: No shader is attached");
#endif
        } else {
            glUniform4ui(GetUniformLocation(name), value[0], value[1], value[2], value[3]);
        }
    }
    
    void SetShaderFloatArray(const std::string& name, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderFloatArray: No shader is attached");
#endif
        } else {
            glUniform1fv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderIntArray(const std::string& name, const uint count, const int* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderIntArray: No shader is attached");
#endif
        } else {
            glUniform1iv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderUIntArray(const std::string& name, const uint count, const uint* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderUIntArray: No shader is attached");
#endif
        } else {
            glUniform1uiv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderVec2Array(const std::string& name, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderVec2Array: No shader is attached");
#endif
        } else {
            glUniform2fv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderIVec2Array(const std::string& name, const uint count, const int* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderIVec2Array: No shader is attached");
#endif
        } else {
            glUniform2iv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderUIVec2Array(const std::string& name, const uint count, const uint* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderUIVec2Array: No shader is attached");
#endif
        } else {
            glUniform2uiv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderVec3Array(const std::string& name, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderVec3Array: No shader is attached");
#endif
        } else {
            glUniform3fv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderIVec3Array(const std::string& name, const uint count, const int* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderIVec3Array: No shader is attached");
#endif
        } else {
            glUniform3iv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderUIVec3Array(const std::string& name, const uint count, const uint* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderUIVec3Array: No shader is attached");
#endif
        } else {
            glUniform3uiv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderVec4Array(const std::string& name, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderVec4Array: No shader is attached");
#endif
        } else {
            glUniform4fv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderIVec4Array(const std::string& name, const uint count, const int* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderIVec4Array: No shader is attached");
#endif
        } else {
            glUniform4iv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderUIVec4Array(const std::string& name, const uint count, const uint* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderUIVec4Array: No shader is attached");
#endif
        } else {
            glUniform4uiv(GetUniformLocation(name), count, value);
        }
    }
    
    void SetShaderMatrix2x2(const std::string& name, const bool swap, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderMatrix2x2: No shader is attached");
#endif
        } else {
            glUniformMatrix2fv(GetUniformLocation(name), count, swap, value);
        }
    }
    
    void SetShaderMatrix3x3(const std::string& name, const bool swap, const uint count,  const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderMatrix3x3: No shader is attached");
#endif
        } else {
            glUniformMatrix3fv(GetUniformLocation(name), count, swap, value);
        }
    }
    
    void SetShaderMatrix4x4(const std::string& name, const bool swap, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderMatrix4x4: No shader is attached");
#endif
        } else {
            glUniformMatrix4fv(GetUniformLocation(name), count, swap, value);
        }
    }
    
    void SetShaderMatrix2x3(const std::string& name, const bool swap, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderMatrix2x3: No shader is attached");
#endif
        } else {
            glUniformMatrix2x3fv(GetUniformLocation(name), count, swap, value);
        }
    }
    
    void SetShaderMatrix3x2(const std::string& name, const bool swap, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderMatrix3x2: No shader is attached");
#endif
        } else {
            glUniformMatrix3x2fv(GetUniformLocation(name), count, swap, value);
        }
    }
    
    void SetShaderMatrix2x4(const std::string& name, const bool swap, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderMatrix2x4: No shader is attached");
#endif
        } else {
            glUniformMatrix2x4fv(GetUniformLocation(name), count, swap, value);
        }
    }
    
    void SetShaderMatrix4x2(const std::string& name, const bool swap, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderMatrix4x2: No shader is attached");
#endif
        } else {
            glUniformMatrix4x2fv(GetUniformLocation(name), count, swap, value);
        }
    }
    
    void SetShaderMatrix3x4(const std::string& name, const bool swap, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderMatrix3x4: No shader is attached");
#endif
        } else {
            glUniformMatrix3x4fv(GetUniformLocation(name), count, swap, value);
        }
    }
    
    void SetShaderMatrix4x3(const std::string& name, const bool swap, const uint count, const float* const value)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderMatrix4x3: No shader is attached");
#endif
        } else {
            glUniformMatrix4x3fv(GetUniformLocation(name), count, swap, value);
        }
    }

    void SetShaderTexture(const std::string& texture, const uint slot)
    {
        if (current_shader == nullptr) {
#ifdef VIOLET_DEBUG
            LogError("SetShaderTexture: No shader is attached");
#endif
        } else {
            glActiveTexture(GL_TEXTURE0 + slot);
            BindTexture(texture);
        }
    }

    Shader::Shader(const std::string& id, const std::string& vertex_code, const std::string& frag_code)
    {
        char        log[512];
        int         success;
        const char* vertex_code_c = vertex_code.c_str();
        const char* frag_code_c   = frag_code.c_str();

        this->id = id;

        uint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_code_c, nullptr);
        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

        if (success == 0) {
#ifdef VIOLET_DEBUG
            glGetShaderInfoLog(vertex_shader, 512, nullptr, log);
            LogError("Failed to compile vertex shader code for shader program \"" + id + "\":\n" + log);
#endif
            return;
        }
#ifdef VIOLET_DEBUG
        LogInfo("Compiled vertex shader code for shader program \"" + id + "\"");
#endif

        uint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag_shader, 1, &frag_code_c, nullptr);
        glCompileShader(frag_shader);
        glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);

        if (success == 0) {
#ifdef VIOLET_DEBUG
            glGetShaderInfoLog(frag_shader, 512, nullptr, log);
            LogError("Failed to compile fragment shader code for shader program \"" + id + "\":\n" + log);
#endif 
            glDeleteShader(vertex_shader);
            return;
        }
#ifdef VIOLET_DEBUG
        LogInfo("Compiled fragment shader code for shader program \"" + id + "\"");
#endif

        this->program = glCreateProgram();
        glAttachShader(this->program, vertex_shader);
        glAttachShader(this->program, frag_shader);
        glLinkProgram(this->program);
        glGetProgramiv(this->program, GL_LINK_STATUS, &success);

        if (success == 0) {
#ifdef VIOLET_DEBUG
            glGetProgramInfoLog(this->program, 512, nullptr, log);
            LogError("Failed to link code for shader program \"" + id + "\":\n" + log);
#endif
            glDeleteProgram(this->program);
            this->program = 0;
        } else {
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
        if (this->program != 0) {
            glDeleteProgram(this->program);
#ifdef VIOLET_DEBUG
            LogInfo("Destroyed shader program \"" + this->id + "\"");
#endif
        }
    }

    std::string Shader::GetId() const
    {
        return this->id;
    }

    GLuint Shader::GetProgram() const
    {
        return this->program;
    }

    void Shader::Attach() const
    {
        if (current_shader != this) {
            current_shader = this;
            glUseProgram(this->program);
        }
    }

    GLint Shader::GetUniform(const std::string& name) const
    {
        return glGetUniformLocation(this->program, name.c_str());
    }
    
    ShaderGroup::~ShaderGroup()
    {
        this->DestroyAllShaders();
    }

    Shader* ShaderGroup::GetShader(const std::string& id) const
    {
        auto shader = this->shaders.find(id);
        if (shader != this->shaders.end()) {
            return shader->second;
        }
        return nullptr;
    }

    void ShaderGroup::AddShader(const std::string& id, Shader* shader)
    {
        this->DestroyShader(id);
        this->shaders.insert({id, shader});
    }
    
    void ShaderGroup::DestroyShader(const std::string& id)
    {
        Shader* shader = GetShader(id);
        if (shader != nullptr) {
            delete shader;
            this->shaders.erase(id);
        }
    }
    
    void ShaderGroup::DestroyAllShaders()
    {
        for (auto shader : this->shaders) {
            delete shader.second;
        }
        this->shaders.clear();
    }
}