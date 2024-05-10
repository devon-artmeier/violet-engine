#include "violet_engine_internal.hpp"

namespace Violet
{
    class ShaderGroup
    {
        public:
            typedef std::unordered_map<std::string, Pointer<Shader>> ShaderMap;

            ShaderMap shaders;
            GLuint    current_shader{ 0 };
    };

    static Pointer<ShaderGroup> shader_group{ nullptr };

    Shader::Shader(const std::string& id, const std::string& vertex_code, const std::string& frag_code)
    {
        this->id = id;

        char        log[512];
        int         success;
        const char* vertex_code_c = vertex_code.c_str();
        const char* frag_code_c   = frag_code.c_str();

#ifdef VIOLET_DEBUG
        LogInfo(this->id + ": Compiling vertex shader");
#endif

        uint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_code_c, nullptr);
        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        glGetShaderInfoLog(vertex_shader, 512, nullptr, log);

        if (success == 0) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Failed to compile vertex shader:\n" + log);
#endif
            return;
        }

#ifdef VIOLET_DEBUG
        LogInfo(this->id + ": Compiling fragment shader");
#endif

        uint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag_shader, 1, &frag_code_c, nullptr);
        glCompileShader(frag_shader);
        glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
        glGetShaderInfoLog(frag_shader, 512, nullptr, log);

        if (success == 0) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Failed to compile fragment shader:\n" + log);
#endif
            glDeleteShader(vertex_shader);
            return;
        }

#ifdef VIOLET_DEBUG
        LogInfo(this->id + ": Linking shaders");
#endif

        this->program = glCreateProgram();
        glAttachShader(this->program, vertex_shader);
        glAttachShader(this->program, frag_shader);
        glLinkProgram(this->program);
        glGetProgramiv(this->program, GL_LINK_STATUS, &success);
        glGetProgramInfoLog(this->program, 512, nullptr, log);
        glDeleteShader(vertex_shader);
        glDeleteShader(frag_shader);

        if (success == 0) {
#ifdef VIOLET_DEBUG
            LogError(this->id + ": Failed to link shaders:\n" + log);
#endif
            return;
        }

#ifdef VIOLET_DEBUG
        LogInfo(this->id + ": Compiled successfully");
#endif
        this->loaded = true;
    }

    Shader::~Shader()
    {
        if (this->loaded) {
            if (shader_group->current_shader == this->program) {
                shader_group->current_shader = 0;
            }
            glDeleteProgram(this->program);
#ifdef VIOLET_DEBUG
            LogInfo(this->id + ": Destroyed");
#endif
        }
    }

    void Shader::Attach() const
    {
        if (shader_group->current_shader != this->program) {
            shader_group->current_shader = this->program;
            glUseProgram(this->program);
        }
    }

    Pointer<Shader> GetShader(const std::string& id)
    {
        auto shader = shader_group->shaders.find(id);
        if (shader != shader_group->shaders.end()) {
            return shader->second;
        }
        return Pointer<Shader>(nullptr);
    }

    void InitShaderGroup()
    {
        shader_group = new ShaderGroup();
    }

    void DestroyShaderGroup()
    {
        shader_group = nullptr;
    }

    void AttachShader(const std::string& id)
    {
        const Pointer<Shader>& shader = GetShader(id);
        if (shader != nullptr) {
            shader->Attach();
        }
    }

    void DetachShader()
    {
        shader_group->current_shader = 0;
    }
    
    static bool CheckShaderSetFail(const std::string& type_name)
    {
        if (shader_group->current_shader == 0) {
#ifdef VIOLET_DEBUG
            LogError("Tried to set " + type_name + " when no shader is attached");
#endif
            return true;
        }
        return false;
    }

    static int GetUniformLocation(const std::string& name)
    {
        if (shader_group->current_shader != 0) {
            return glGetUniformLocation(shader_group->current_shader, name.c_str());
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
    
    void SetShaderVector2(const std::string& name, const Vector2& vec)
    {
        if (!CheckShaderSetFail("2D vector")) {
            glUniform2f(GetUniformLocation(name), vec[0], vec[1]);
        }
    }
    
    void SetShaderIVector2(const std::string& name, const IVector2& vec)
    {
        if (!CheckShaderSetFail("2D int vector")) {
            glUniform2i(GetUniformLocation(name), vec[0], vec[1]);
        }
    }
    
    void SetShaderUIVector2(const std::string& name, const UIVector2& vec)
    {
        if (!CheckShaderSetFail("2D unsigned int vector")) {
            glUniform2ui(GetUniformLocation(name), vec[0], vec[1]);
        }
    }
    
    void SetShaderVector3(const std::string& name, const Vector3& vec)
    {
        if (!CheckShaderSetFail("3D vector")) {
            glUniform3f(GetUniformLocation(name), vec[0], vec[1], vec[2]);
        }
    }
    
    void SetShaderIVector3(const std::string& name, const IVector3& vec)
    {
        if (!CheckShaderSetFail("3D int vector")) {
            glUniform3i(GetUniformLocation(name), vec[0], vec[1], vec[2]);
        }
    }
    
    void SetShaderUIVector3(const std::string& name, const UIVector3& vec)
    {
        if (!CheckShaderSetFail("3D unsigned int vector")) {
            glUniform3ui(GetUniformLocation(name), vec[0], vec[1], vec[2]);
        }
    }
    
    void SetShaderVector4(const std::string& name, const Vector4& vec)
    {
        if (!CheckShaderSetFail("4D vector")) {
            glUniform4f(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
        }
    }
    
    void SetShaderIVector4(const std::string& name, const IVector4& vec)
    {
        if (!CheckShaderSetFail("4D int vector")) {
            glUniform4i(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
        }
    }
    
    void SetShaderUIVector4(const std::string& name, const UIVector4& vec)
    {
        if (!CheckShaderSetFail("4D unsigned int vector")) {
            glUniform4ui(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
        }
    }
    
    void SetShaderFloatArray(const std::string& name, std::initializer_list<float> values)
    {
        if (!CheckShaderSetFail("float array")) {
            glUniform1fv(GetUniformLocation(name), values.size(), values.begin());
        }
    }
    
    void SetShaderIntArray(const std::string& name, std::initializer_list<int> values)
    {
        if (!CheckShaderSetFail("int array")) {
            glUniform1iv(GetUniformLocation(name), values.size(), values.begin());
        }
    }
    
    void SetShaderUIntArray(const std::string& name, std::initializer_list<uint> values)
    {
        if (!CheckShaderSetFail("unsigned int array")) {
            glUniform1uiv(GetUniformLocation(name), values.size(), values.begin());
        }
    }
    
    void SetShaderVector2Array(const std::string& name, std::initializer_list<Vector2> vecs)
    {
        if (!CheckShaderSetFail("2D vector array")) {
            Pointer<float> values = new float[vecs.size() * 2];
            int i = 0;
            for (const Vector2& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
            }
            glUniform2fv(GetUniformLocation(name), vecs.size(), values.Raw());
        }
    }
    
    void SetShaderIVector2Array(const std::string& name, std::initializer_list<IVector2> vecs)
    {
        if (!CheckShaderSetFail("2D int vector array")) {
            Pointer<int> values = new int[vecs.size() * 2];
            int i = 0;
            for (const IVector2& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
            }
            glUniform2iv(GetUniformLocation(name), vecs.size(), values.Raw());
        }
    }
    
    void SetShaderUIVector2Array(const std::string& name, std::initializer_list<UIVector2> vecs)
    {
        if (!CheckShaderSetFail("2D unsigned int vector array")) {
            Pointer<uint> values = new uint[vecs.size() * 2];
            int i = 0;
            for (const UIVector2& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
            }
            glUniform2uiv(GetUniformLocation(name), vecs.size(), values.Raw());
        }
    }
    
    void SetShaderVector3Array(const std::string& name, std::initializer_list<Vector3> vecs)
    {
        if (!CheckShaderSetFail("3D vector array")) {
            Pointer<float> values = new float[vecs.size() * 3];
            int i = 0;
            for (const Vector3& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
            }
            glUniform3fv(GetUniformLocation(name), vecs.size(), values.Raw());
        }
    }
    
    void SetShaderIVector3Array(const std::string& name, std::initializer_list<IVector3> vecs)
    {
        if (!CheckShaderSetFail("3D int vector array")) {
            Pointer<int> values = new int[vecs.size() * 3];
            int i = 0;
            for (const IVector3& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
            }
            glUniform3iv(GetUniformLocation(name), vecs.size(), values.Raw());
        }
    }
    
    void SetShaderUIVector3Array(const std::string& name, std::initializer_list<UIVector3> vecs)
    {
        if (!CheckShaderSetFail("3D unsigned int vector array")) {
            Pointer<uint> values = new uint[vecs.size() * 3];
            int i = 0;
            for (const UIVector3& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
            }
            glUniform3uiv(GetUniformLocation(name), vecs.size(), values.Raw());
        }
    }
    
    void SetShaderVector4Array(const std::string& name, std::initializer_list<Vector4> vecs)
    {
        if (!CheckShaderSetFail("4D vector array")) {
            Pointer<float> values = new float[vecs.size() * 4];
            int i = 0;
            for (const Vector4& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
                values[i++] = vec[3];
            }
            glUniform4fv(GetUniformLocation(name), vecs.size(), values.Raw());
        }
    }
    
    void SetShaderIVector4Array(const std::string& name, std::initializer_list<IVector4> vecs)
    {
        if (!CheckShaderSetFail("4D int vector array")) {
            Pointer<int> values = new int[vecs.size() * 4];
            int i = 0;
            for (const IVector4& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
                values[i++] = vec[3];
            }
            glUniform4iv(GetUniformLocation(name), vecs.size(), values.Raw());
        }
    }
    
    void SetShaderUIVector4Array(const std::string& name, std::initializer_list<UIVector4> vecs)
    {
        if (!CheckShaderSetFail("4D unsigned int vector array")) {
            Pointer<uint> values = new uint[vecs.size() * 4];
            int i = 0;
            for (const UIVector4& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
                values[i++] = vec[3];
            }
            glUniform4uiv(GetUniformLocation(name), vecs.size(), values.Raw());
        }
    }
    
    /*void SetShaderMatrix4x2(const std::string& name, const bool swap, const uint count, const float* const value)
    {
        if (!CheckShaderSetFail((std::string)"4x2 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix4x2fv(GetUniformLocation(name), count, swap, value);
        }
    }
    
    void SetShaderMatrix4x3(const std::string& name, const bool swap, const uint count, const float* const value)
    {
        if (!CheckShaderSetFail((std::string)"4x3 matrix" + ((count > 1) ? "array" : ""))) {
            glUniformMatrix4x3fv(GetUniformLocation(name), count, swap, value);
        }
    }*/

    void SetShaderMatrix2x2(const std::string& name, const Matrix2x2& mat)
    {
        if (!CheckShaderSetFail("2x2 matrix")) {
            float values[] = {
                mat[0][0], mat[0][1],
                mat[1][0], mat[1][1]
            };
            glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, values);
        }
    }

    void SetShaderMatrix2x3(const std::string& name, const Matrix2x3& mat)
    {
        if (!CheckShaderSetFail("2x3 matrix")) {
            float values[] = {
                mat[0][0], mat[0][1],
                mat[1][0], mat[1][1],
                mat[2][0], mat[2][1]
            };
            glUniformMatrix2x3fv(GetUniformLocation(name), 1, GL_FALSE, values);
        }
    }

    void SetShaderMatrix2x4(const std::string& name, const Matrix2x4& mat)
    {
        if (!CheckShaderSetFail("2x4 matrix")) {
            float values[] = {
                mat[0][0], mat[0][1],
                mat[1][0], mat[1][1],
                mat[2][0], mat[2][1],
                mat[3][0], mat[3][1]
            };
            glUniformMatrix2x4fv(GetUniformLocation(name), 1, GL_FALSE, values);
        }
    }

    void SetShaderMatrix3x2(const std::string& name, const Matrix3x2& mat)
    {
        if (!CheckShaderSetFail("3x2 matrix")) {
            float values[] = {
                mat[0][0], mat[0][1], mat[0][2],
                mat[1][0], mat[1][1], mat[1][2]
            };
            glUniformMatrix3x2fv(GetUniformLocation(name), 1, GL_FALSE, values);
        }
    }

    void SetShaderMatrix3x3(const std::string& name, const Matrix3x3& mat)
    {
        if (!CheckShaderSetFail("3x3 matrix")) {
            float values[] = {
                mat[0][0], mat[0][1], mat[0][2],
                mat[1][0], mat[1][1], mat[1][2],
                mat[2][0], mat[2][1], mat[2][2]
            };
            glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, values);
        }
    }

    void SetShaderMatrix3x4(const std::string& name, const Matrix3x4& mat)
    {
        if (!CheckShaderSetFail("3x4 matrix")) {
            float values[] = {
                mat[0][0], mat[0][1], mat[0][2],
                mat[1][0], mat[1][1], mat[1][2],
                mat[2][0], mat[2][1], mat[2][2],
                mat[3][0], mat[3][1], mat[3][2]
            };
            glUniformMatrix3x4fv(GetUniformLocation(name), 1, GL_FALSE, values);
        }
    }

    void SetShaderMatrix4x4(const std::string& name, const Matrix4x4& mat)
    {
        if (!CheckShaderSetFail("4x4 matrix")) {
            float values[] = {
                mat[0][0], mat[0][1], mat[0][2], mat[0][3],
                mat[1][0], mat[1][1], mat[1][2], mat[1][3],
                mat[2][0], mat[2][1], mat[2][2], mat[2][3],
                mat[3][0], mat[3][1], mat[3][2], mat[3][3]
            };
            glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, values);
        }
    }

    void SetShaderMatrix2x2Array(const std::string& name, std::initializer_list<Matrix2x2> mats)
    {
        if (!CheckShaderSetFail("2x2 matrix array")) {
            Pointer<float> values = new float[mats.size() * 4];
            int i = 0;
            for (const Matrix2x2& mat : mats) {
                values[i++] = mat[0][0];
                values[i++] = mat[0][1];
                values[i++] = mat[1][0];
                values[i++] = mat[1][1];
            }
            glUniformMatrix2fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        }
    }

    void SetShaderMatrix2x3Array(const std::string& name, std::initializer_list<Matrix2x3> mats)
    {
        if (!CheckShaderSetFail("2x3 matrix array")) {
            Pointer<float> values = new float[mats.size() * 6];
            int i = 0;
            for (const Matrix2x3& mat : mats) {
                values[i++] = mat[0][0];
                values[i++] = mat[0][1];
                values[i++] = mat[1][0];
                values[i++] = mat[1][1];
                values[i++] = mat[2][0];
                values[i++] = mat[2][1];
            }
            glUniformMatrix2x3fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        }
    }

    void SetShaderMatrix2x4Array(const std::string& name, std::initializer_list<Matrix2x4> mats)
    {
        if (!CheckShaderSetFail("2x4 matrix array")) {
            Pointer<float> values = new float[mats.size() * 8];
            int i = 0;
            for (const Matrix2x4& mat : mats) {
                values[i++] = mat[0][0];
                values[i++] = mat[0][1];
                values[i++] = mat[1][0];
                values[i++] = mat[1][1];
                values[i++] = mat[2][0];
                values[i++] = mat[2][1];
                values[i++] = mat[3][0];
                values[i++] = mat[3][1];
            }
            glUniformMatrix2x4fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        }
    }

    void SetShaderMatrix3x2Array(const std::string& name, std::initializer_list<Matrix3x2> mats)
    {
        if (!CheckShaderSetFail("3x2 matrix array")) {
            Pointer<float> values = new float[mats.size() * 6];
            int i = 0;
            for (const Matrix3x2& mat : mats) {
                values[i++] = mat[0][0];
                values[i++] = mat[0][1];
                values[i++] = mat[0][2];
                values[i++] = mat[1][0];
                values[i++] = mat[1][1];
                values[i++] = mat[1][2];
            }
            glUniformMatrix3x2fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        }
    }

    void SetShaderMatrix3x3Array(const std::string& name, std::initializer_list<Matrix3x3> mats)
    {
        if (!CheckShaderSetFail("3x3 matrix array")) {
            Pointer<float> values = new float[mats.size() * 9];
            int i = 0;
            for (const Matrix3x3& mat : mats) {
                values[i++] = mat[0][0];
                values[i++] = mat[0][1];
                values[i++] = mat[0][2];
                values[i++] = mat[1][0];
                values[i++] = mat[1][1];
                values[i++] = mat[1][2];
                values[i++] = mat[2][0];
                values[i++] = mat[2][1];
                values[i++] = mat[2][2];
            }
            glUniformMatrix3fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        }
    }

    void SetShaderMatrix3x4Array(const std::string& name, std::initializer_list<Matrix3x4> mats)
    {
        if (!CheckShaderSetFail("3x4 matrix array")) {
            Pointer<float> values = new float[mats.size() * 12];
            int i = 0;
            for (const Matrix3x4& mat : mats) {
                values[i++] = mat[0][0];
                values[i++] = mat[0][1];
                values[i++] = mat[0][2];
                values[i++] = mat[1][0];
                values[i++] = mat[1][1];
                values[i++] = mat[1][2];
                values[i++] = mat[2][0];
                values[i++] = mat[2][1];
                values[i++] = mat[2][2];
                values[i++] = mat[3][0];
                values[i++] = mat[3][1];
                values[i++] = mat[3][2];
            }
            glUniformMatrix3fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        }
    }

    void SetShaderMatrix4x4Array(const std::string& name, std::initializer_list<Matrix4x4> mats)
    {
        if (!CheckShaderSetFail("4x4 matrix array")) {
            Pointer<float> values = new float[mats.size() * 16];
            int i = 0;
            for (const Matrix4x4& mat : mats) {
                values[i++] = mat[0][0];
                values[i++] = mat[0][1];
                values[i++] = mat[0][2];
                values[i++] = mat[0][3];
                values[i++] = mat[1][0];
                values[i++] = mat[1][1];
                values[i++] = mat[1][2];
                values[i++] = mat[1][3];
                values[i++] = mat[2][0];
                values[i++] = mat[2][1];
                values[i++] = mat[2][2];
                values[i++] = mat[2][3];
                values[i++] = mat[3][0];
                values[i++] = mat[3][1];
                values[i++] = mat[3][2];
                values[i++] = mat[3][3];
            }
            glUniformMatrix4fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        }
    }

    void SetShaderTexture(const std::string& texture, const uint slot)
    {
        if (!CheckShaderSetFail("texture")) {
            glActiveTexture(GL_TEXTURE0 + slot);
            BindTexture(texture);
        }
    }

    void SetShaderTexture(const Pointer<Texture>& texture, const uint slot)
    {
        if (!CheckShaderSetFail("texture")) {
            glActiveTexture(GL_TEXTURE0 + slot);
            texture->Bind();
        }
    }
}