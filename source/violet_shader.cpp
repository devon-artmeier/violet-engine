#include "violet_message_internal.hpp"
#include "violet_shader_internal.hpp"
#include "violet_texture_internal.hpp"

namespace Violet
{
    static Pointer<ResourceGroup<Shader>> shader_group  { nullptr };
    static GLuint                         current_shader{ 0 };

    void InitShaderGroup()
    {
        shader_group = new ResourceGroup<Shader>();
    }

    void CloseShaderGroup()
    {
        shader_group = nullptr;
    }

    void LoadShader(const std::string& id, const std::string& vertex_code, const std::string& frag_code)
    {
        Pointer<Shader> shader(new Shader(id, vertex_code, frag_code));
        if (shader->GetProgram() != 0) {
            shader_group->Add(id, shader);
        }
    }

    void DestroyShader(const std::string& id)
    {
        shader_group->Destroy(id);
    }
    
    void AttachShader(const std::string& id)
    {
        Pointer<Shader> shader = shader_group->Get(id);
        if (shader != nullptr) {
            shader->Attach();
        }
    }

    void DetachShader()
    {
        current_shader = 0;
    }
    
    static bool CheckShaderSetFail(const std::string& type_name)
    {
        if (current_shader == 0) {
#ifdef VIOLET_DEBUG
            LogError("Tried to set " + type_name + " when no shader is attached");
#endif
            return true;
        }
        return false;
    }

    static int GetUniformLocation(const std::string& name)
    {
        if (current_shader != 0) {
            return glGetUniformLocation(current_shader, name.c_str());
        }
        return 0;
    }

    void SetShaderFloat(const std::string& name, const float value)
    {
        if (!CheckShaderSetFail("float")) {
            glUniform1f(GetUniformLocation(name), value);
        }
    }
    
    void SetShaderInt(const std::string& name, const int value)
    {
        if (!CheckShaderSetFail("int")) {
            glUniform1i(GetUniformLocation(name), value);
        }
    }
    
    void SetShaderUInt(const std::string& name, const uint value)
    {
        if (!CheckShaderSetFail("unsigned int")) {
            glUniform1ui(GetUniformLocation(name), value);
        }
    }
    
    void SetShaderVec2(const std::string& name, const float value[2])
    {
        if (!CheckShaderSetFail("2D vector")) {
            glUniform2f(GetUniformLocation(name), value[0], value[1]);
        }
    }
    
    void SetShaderIVec2(const std::string& name, const int value[2])
    {
        if (!CheckShaderSetFail("2D int vector")) {
            glUniform2i(GetUniformLocation(name), value[0], value[1]);
        }
    }
    
    void SetShaderUIVec2(const std::string& name, const uint value[2])
    {
        if (!CheckShaderSetFail("2D unsigned int vector")) {
            glUniform2ui(GetUniformLocation(name), value[0], value[1]);
        }
    }
    
    void SetShaderVec3(const std::string& name, const float value[3])
    {
        if (!CheckShaderSetFail("3D vector")) {
            glUniform3f(GetUniformLocation(name), value[0], value[1], value[2]);
        }
    }
    
    void SetShaderIVec3(const std::string& name, const int value[3])
    {
        if (!CheckShaderSetFail("3D int vector")) {
            glUniform3i(GetUniformLocation(name), value[0], value[1], value[2]);
        }
    }
    
    void SetShaderUIVec3(const std::string& name, const uint value[3])
    {
        if (!CheckShaderSetFail("3D unsigned int vector")) {
            glUniform3ui(GetUniformLocation(name), value[0], value[1], value[2]);
        }
    }
    
    void SetShaderVec4(const std::string& name, const float value[4])
    {
        if (!CheckShaderSetFail("4D vector")) {
            glUniform4f(GetUniformLocation(name), value[0], value[1], value[2], value[3]);
        }
    }
    
    void SetShaderIVec4(const std::string& name, const int value[4])
    {
        if (!CheckShaderSetFail("4D int vector")) {
            glUniform4i(GetUniformLocation(name), value[0], value[1], value[2], value[3]);
        }
    }
    
    void SetShaderUIVec4(const std::string& name, const uint value[4])
    {
        if (!CheckShaderSetFail("4D unsigned int vector")) {
            glUniform4ui(GetUniformLocation(name), value[0], value[1], value[2], value[3]);
        }
    }
    
    void SetShaderFloatArray(const std::string& name, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail("float array")) {
            glUniform1fv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderIntArray(const std::string& name, const uint count, const Pointer<int> value)
    {
        if (!CheckShaderSetFail("int array")) {
            glUniform1iv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderUIntArray(const std::string& name, const uint count, const Pointer<uint> value)
    {
        if (!CheckShaderSetFail("unsigned int array")) {
            glUniform1uiv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderVec2Array(const std::string& name, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail("2D vector array")) {
            glUniform2fv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderIVec2Array(const std::string& name, const uint count, const Pointer<int> value)
    {
        if (!CheckShaderSetFail("2D int vector array")) {
            glUniform2iv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderUIVec2Array(const std::string& name, const uint count, const Pointer<uint> value)
    {
        if (!CheckShaderSetFail("2D unsigned int vector array")) {
            glUniform2uiv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderVec3Array(const std::string& name, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail("3D vector array")) {
            glUniform3fv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderIVec3Array(const std::string& name, const uint count, const Pointer<int> value)
    {
        if (!CheckShaderSetFail("3D int vector array")) {
            glUniform3iv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderUIVec3Array(const std::string& name, const uint count, const Pointer<uint> value)
    {
        if (!CheckShaderSetFail("3D unsigned int vector array")) {
            glUniform3uiv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderVec4Array(const std::string& name, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail("4D vector array")) {
            glUniform4fv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderIVec4Array(const std::string& name, const uint count, const Pointer<int> value)
    {
        if (!CheckShaderSetFail("4D int vector array")) {
            glUniform4iv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderUIVec4Array(const std::string& name, const uint count, const Pointer<uint> value)
    {
        if (!CheckShaderSetFail("4D unsigned int vector array")) {
            glUniform4uiv(GetUniformLocation(name), count, value.Raw());
        }
    }
    
    void SetShaderMatrix2x2(const std::string& name, const bool swap, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail((std::string)"2x2 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix2fv(GetUniformLocation(name), count, swap, value.Raw());
        }
    }
    
    void SetShaderMatrix3x3(const std::string& name, const bool swap, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail((std::string)"3x3 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix3fv(GetUniformLocation(name), count, swap, value.Raw());
        }
    }
    
    void SetShaderMatrix4x4(const std::string& name, const bool swap, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail((std::string)"4x4 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix4fv(GetUniformLocation(name), count, swap, value.Raw());
        }
    }
    
    void SetShaderMatrix2x3(const std::string& name, const bool swap, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail((std::string)"2x3 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix2x3fv(GetUniformLocation(name), count, swap, value.Raw());
        }
    }
    
    void SetShaderMatrix3x2(const std::string& name, const bool swap, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail((std::string)"3x3 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix3x2fv(GetUniformLocation(name), count, swap, value.Raw());
        }
    }
    
    void SetShaderMatrix2x4(const std::string& name, const bool swap, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail((std::string)"2x4 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix2x4fv(GetUniformLocation(name), count, swap, value.Raw());
        }
    }
    
    void SetShaderMatrix4x2(const std::string& name, const bool swap, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail((std::string)"4x2 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix4x2fv(GetUniformLocation(name), count, swap, value.Raw());
        }
    }
    
    void SetShaderMatrix3x4(const std::string& name, const bool swap, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail((std::string)"3x4 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix3x4fv(GetUniformLocation(name), count, swap, value.Raw());
        }
    }
    
    void SetShaderMatrix4x3(const std::string& name, const bool swap, const uint count, const Pointer<float> value)
    {
        if (!CheckShaderSetFail((std::string)"4x3 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix4x3fv(GetUniformLocation(name), count, swap, value.Raw());
        }
    }

    void SetShaderTexture(const std::string& texture, const uint slot)
    {
        if (!CheckShaderSetFail("texture")) {
            glActiveTexture(GL_TEXTURE0 + slot);
            BindTexture(texture);
        }
    }

    Shader::Shader(const std::string& id, const std::string& vertex_code, const std::string& frag_code) : Resource(id)
    {
        char        log[512];
        int         success;
        const char* vertex_code_c = vertex_code.c_str();
        const char* frag_code_c   = frag_code.c_str();

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
        if (current_shader == this->program) {
            current_shader = 0;
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
        if (current_shader != this->program) {
            current_shader = this->program;
            glUseProgram(this->program);
        }
    }

    GLint Shader::GetUniform(const std::string& name) const
    {
        return glGetUniformLocation(this->program, name.c_str());
    }
}