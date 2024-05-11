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

        LogInfo("Compiling vertex shader code for shader \"" + this->id + "\"");

        uint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_code_c, nullptr);
        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        glGetShaderInfoLog(vertex_shader, 512, nullptr, log);

        if (success == 0) {
            LogError("Failed to compile vertex shader code for shader \"" + this->id + "\":\n" + log);
        } else {
            LogInfo("Compiling fragment shader code for shader \"" + this->id + "\"");

            uint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(frag_shader, 1, &frag_code_c, nullptr);
            glCompileShader(frag_shader);
            glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
            glGetShaderInfoLog(frag_shader, 512, nullptr, log);

            if (success == 0) {
                LogError("Failed to compile fragment shader code for shader \"" + this->id + "\":\n" + log);
                glDeleteShader(vertex_shader);
            } else {
                LogInfo("Linking code for shader \"" + this->id + "\"");

                this->program = glCreateProgram();
                glAttachShader(this->program, vertex_shader);
                glAttachShader(this->program, frag_shader);
                glLinkProgram(this->program);
                glGetProgramiv(this->program, GL_LINK_STATUS, &success);
                glGetProgramInfoLog(this->program, 512, nullptr, log);
                glDeleteShader(vertex_shader);
                glDeleteShader(frag_shader);

                if (success == 0) {
                    LogError("Failed to link code for shader \"" + this->id + "\":\n" + log);
                } else {
                    LogInfo("Compiled shader \"" + this->id + "\" successfully");
                }
            }
        }
    }

    Shader::~Shader()
    {
        if (this->program != 0) {
            if (shader_group->current_shader == this->program) {
                shader_group->current_shader = 0;
            }
            glDeleteProgram(this->program);
        }
        LogInfo("Destroyed shader \"" + this->id + "\"");
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

    void LoadShader(const std::string& id, const std::string& vertex_code, const std::string& frag_code)
    {
        if (GetShader(id) == nullptr) {
            Pointer<Shader> shader = new Shader(id, vertex_code, frag_code);

            if (shader->program != 0) {
                shader_group->shaders.insert({ id, shader });
            }
        } else {
            LogError("LoadShader: \"" + id + "\" is already loaded");
        }
    }

    void DestroyShader(const std::string& id)
    {
        if (GetShader(id) != nullptr) {
            shader_group->shaders.erase(id);
        } else {
            LogError("DestroyShader: \"" + id + "\" doesn't exist");
        }
    }

    void DestroyAllShaders()
    {
        shader_group->shaders.clear();
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
        } else {
            LogError("AttachShader: \"" + id + "\" doesn't exist");
        }
    }

    void DetachShader()
    {
        shader_group->current_shader = 0;
    }

    static int GetUniformLocation(const std::string& name)
    {
        return glGetUniformLocation(shader_group->current_shader, name.c_str());
    }

    void SetShaderFloat(const std::string& name, const float value)
    {
        if (shader_group->current_shader != 0) {
            glUniform1f(GetUniformLocation(name), value);
        } else {
            LogError("SetShaderFloat: No shader attached");
        }
    }
    
    void SetShaderInt(const std::string& name, const int value)
    {
        if (shader_group->current_shader != 0) {
            glUniform1i(GetUniformLocation(name), value);
        } else {
            LogError("SetShaderInt: No shader attached");
        }
    }
    
    void SetShaderUInt(const std::string& name, const uint value)
    {
        if (shader_group->current_shader != 0) {
            glUniform1ui(GetUniformLocation(name), value);
        } else {
            LogError("SetShaderUInt: No shader attached");
        }
    }
    
    void SetShaderVector2(const std::string& name, const Vector2& vec)
    {
        if (shader_group->current_shader != 0) {
            glUniform2f(GetUniformLocation(name), vec[0], vec[1]);
        } else {
            LogError("SetShaderVector2: No shader attached");
        }
    }
    
    void SetShaderIVector2(const std::string& name, const IVector2& vec)
    {
        if (shader_group->current_shader != 0) {
            glUniform2i(GetUniformLocation(name), vec[0], vec[1]);
        } else {
            LogError("SetShaderIVector2: No shader attached");
        }
    }
    
    void SetShaderUIVector2(const std::string& name, const UIVector2& vec)
    {
        if (shader_group->current_shader != 0) {
            glUniform2ui(GetUniformLocation(name), vec[0], vec[1]);
        } else {
            LogError("SetShaderUIVector2: No shader attached");
        }
    }
    
    void SetShaderVector3(const std::string& name, const Vector3& vec)
    {
        if (shader_group->current_shader != 0) {
            glUniform3f(GetUniformLocation(name), vec[0], vec[1], vec[2]);
        } else {
            LogError("SetShaderVector3: No shader attached");
        }
    }
    
    void SetShaderIVector3(const std::string& name, const IVector3& vec)
    {
        if (shader_group->current_shader != 0) {
            glUniform3i(GetUniformLocation(name), vec[0], vec[1], vec[2]);
        } else {
            LogError("SetShaderIVector3: No shader attached");
        }
    }
    
    void SetShaderUIVector3(const std::string& name, const UIVector3& vec)
    {
        if (shader_group->current_shader != 0) {
            glUniform3ui(GetUniformLocation(name), vec[0], vec[1], vec[2]);
        } else {
            LogError("SetShaderUIVector3: No shader attached");
        }
    }
    
    void SetShaderVector4(const std::string& name, const Vector4& vec)
    {
        if (shader_group->current_shader != 0) {
            glUniform4f(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
        } else {
            LogError("SetShaderVector4: No shader attached");
        }
    }
    
    void SetShaderIVector4(const std::string& name, const IVector4& vec)
    {
        if (shader_group->current_shader != 0) {
            glUniform4i(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
        } else {
            LogError("SetShaderIVector4: No shader attached");
        }
    }
    
    void SetShaderUIVector4(const std::string& name, const UIVector4& vec)
    {
        if (shader_group->current_shader != 0) {
            glUniform4ui(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
        } else {
            LogError("SetShaderUIVector4: No shader attached");
        }
    }
    
    void SetShaderFloatArray(const std::string& name, std::initializer_list<float> values)
    {
        if (shader_group->current_shader != 0) {
            glUniform1fv(GetUniformLocation(name), values.size(), values.begin());
        } else {
            LogError("SetShaderFloatArray: No shader attached");
        }
    }
    
    void SetShaderIntArray(const std::string& name, std::initializer_list<int> values)
    {
        if (shader_group->current_shader != 0) {
            glUniform1iv(GetUniformLocation(name), values.size(), values.begin());
        } else {
            LogError("SetShaderIntArray: No shader attached");
        }
    }
    
    void SetShaderUIntArray(const std::string& name, std::initializer_list<uint> values)
    {
        if (shader_group->current_shader != 0) {
            glUniform1uiv(GetUniformLocation(name), values.size(), values.begin());
        } else {
            LogError("SetShaderUIntArray: No shader attached");
        }
    }
    
    void SetShaderVector2Array(const std::string& name, std::initializer_list<Vector2> vecs)
    {
        if (shader_group->current_shader != 0) {
            Pointer<float> values = new float[vecs.size() * 2];
            int i = 0;
            for (const Vector2& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
            }
            glUniform2fv(GetUniformLocation(name), vecs.size(), values.Raw());
        } else {
            LogError("SetShaderVector2Array: No shader attached");
        }
    }
    
    void SetShaderIVector2Array(const std::string& name, std::initializer_list<IVector2> vecs)
    {
        if (shader_group->current_shader != 0) {
            Pointer<int> values = new int[vecs.size() * 2];
            int i = 0;
            for (const IVector2& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
            }
            glUniform2iv(GetUniformLocation(name), vecs.size(), values.Raw());
        } else {
            LogError("SetShaderIVector2Array: No shader attached");
        }
    }
    
    void SetShaderUIVector2Array(const std::string& name, std::initializer_list<UIVector2> vecs)
    {
        if (shader_group->current_shader != 0) {
            Pointer<uint> values = new uint[vecs.size() * 2];
            int i = 0;
            for (const UIVector2& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
            }
            glUniform2uiv(GetUniformLocation(name), vecs.size(), values.Raw());
        } else {
            LogError("SetShaderUIVector2Array: No shader attached");
        }
    }
    
    void SetShaderVector3Array(const std::string& name, std::initializer_list<Vector3> vecs)
    {
        if (shader_group->current_shader != 0) {
            Pointer<float> values = new float[vecs.size() * 3];
            int i = 0;
            for (const Vector3& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
            }
            glUniform3fv(GetUniformLocation(name), vecs.size(), values.Raw());
        } else {
            LogError("SetShaderVector3Array: No shader attached");
        }
    }
    
    void SetShaderIVector3Array(const std::string& name, std::initializer_list<IVector3> vecs)
    {
        if (shader_group->current_shader != 0) {
            Pointer<int> values = new int[vecs.size() * 3];
            int i = 0;
            for (const IVector3& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
            }
            glUniform3iv(GetUniformLocation(name), vecs.size(), values.Raw());
        } else {
            LogError("SetShaderIVector3Array: No shader attached");
        }
    }
    
    void SetShaderUIVector3Array(const std::string& name, std::initializer_list<UIVector3> vecs)
    {
        if (shader_group->current_shader != 0) {
            Pointer<uint> values = new uint[vecs.size() * 3];
            int i = 0;
            for (const UIVector3& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
            }
            glUniform3uiv(GetUniformLocation(name), vecs.size(), values.Raw());
        } else {
            LogError("SetShaderUIVector3Array: No shader attached");
        }
    }
    
    void SetShaderVector4Array(const std::string& name, std::initializer_list<Vector4> vecs)
    {
        if (shader_group->current_shader != 0) {
            Pointer<float> values = new float[vecs.size() * 4];
            int i = 0;
            for (const Vector4& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
                values[i++] = vec[3];
            }
            glUniform4fv(GetUniformLocation(name), vecs.size(), values.Raw());
        } else {
            LogError("SetShaderVector4Array: No shader attached");
        }
    }
    
    void SetShaderIVector4Array(const std::string& name, std::initializer_list<IVector4> vecs)
    {
        if (shader_group->current_shader != 0) {
            Pointer<int> values = new int[vecs.size() * 4];
            int i = 0;
            for (const IVector4& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
                values[i++] = vec[3];
            }
            glUniform4iv(GetUniformLocation(name), vecs.size(), values.Raw());
        } else {
            LogError("SetShaderIVector4Array: No shader attached");
        }
    }
    
    void SetShaderUIVector4Array(const std::string& name, std::initializer_list<UIVector4> vecs)
    {
        if (shader_group->current_shader != 0) {
            Pointer<uint> values = new uint[vecs.size() * 4];
            int i = 0;
            for (const UIVector4& vec : vecs) {
                values[i++] = vec[0];
                values[i++] = vec[1];
                values[i++] = vec[2];
                values[i++] = vec[3];
            }
            glUniform4uiv(GetUniformLocation(name), vecs.size(), values.Raw());
        } else {
            LogError("SetShaderUIVector4Array: No shader attached");
        }
    }

    void SetShaderMatrix2x2(const std::string& name, const Matrix2x2& mat)
    {
        if (shader_group->current_shader != 0) {
            glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        } else {
            LogError("SetShaderMatrix2x2: No shader attached");
        }
    }

    void SetShaderMatrix2x3(const std::string& name, const Matrix2x3& mat)
    {
        if (shader_group->current_shader != 0) {
            glUniformMatrix2x3fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        } else {
            LogError("SetShaderMatrix2x3: No shader attached");
        }
    }

    void SetShaderMatrix2x4(const std::string& name, const Matrix2x4& mat)
    {
        if (shader_group->current_shader != 0) {
            glUniformMatrix2x4fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        } else {
            LogError("SetShaderMatrix2x4: No shader attached");
        }
    }

    void SetShaderMatrix3x2(const std::string& name, const Matrix3x2& mat)
    {
        if (shader_group->current_shader != 0) {
            glUniformMatrix3x2fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        } else {
            LogError("SetShaderMatrix3x2: No shader attached");
        }
    }

    void SetShaderMatrix3x3(const std::string& name, const Matrix3x3& mat)
    {
        if (shader_group->current_shader != 0) {
            glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        } else {
            LogError("SetShaderMatrix3x3: No shader attached");
        }
    }

    void SetShaderMatrix3x4(const std::string& name, const Matrix3x4& mat)
    {
        if (shader_group->current_shader != 0) {
            glUniformMatrix3x4fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        } else {
            LogError("SetShaderMatrix3x4: No shader attached");
        }
    }

    void SetShaderMatrix4x2(const std::string& name, const Matrix4x2& mat)
    {
        if (shader_group->current_shader != 0) {
            glUniformMatrix4x2fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        } else {
            LogError("SetShaderMatrix4x2: No shader attached");
        }
    }

    void SetShaderMatrix4x3(const std::string& name, const Matrix4x3& mat)
    {
        if (shader_group->current_shader != 0) {
            glUniformMatrix4x3fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        } else {
            LogError("SetShaderMatrix4x3: No shader attached");
        }
    }

    void SetShaderMatrix4x4(const std::string& name, const Matrix4x4& mat)
    {
        if (shader_group->current_shader != 0) {
            glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        } else {
            LogError("SetShaderMatrix4x4: No shader attached");
        }
    }

    void SetShaderMatrix2x2Array(const std::string& name, std::initializer_list<Matrix2x2> mats)
    {
        if (shader_group->current_shader != 0) {
            Pointer<float> values = new float[mats.size() * 4];
            int i = 0;
            for (const Matrix2x2& mat : mats) {
                values[i++] = mat[0][0];
                values[i++] = mat[0][1];
                values[i++] = mat[1][0];
                values[i++] = mat[1][1];
            }
            glUniformMatrix2fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        } else {
            LogError("SetShaderMatrix2x2Array: No shader attached");
        }
    }

    void SetShaderMatrix2x3Array(const std::string& name, std::initializer_list<Matrix2x3> mats)
    {
        if (shader_group->current_shader != 0) {
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
        } else {
            LogError("SetShaderMatrix2x3Array: No shader attached");
        }
    }

    void SetShaderMatrix2x4Array(const std::string& name, std::initializer_list<Matrix2x4> mats)
    {
        if (shader_group->current_shader != 0) {
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
        } else {
            LogError("SetShaderMatrix2x4Array: No shader attached");
        }
    }

    void SetShaderMatrix3x2Array(const std::string& name, std::initializer_list<Matrix3x2> mats)
    {
        if (shader_group->current_shader != 0) {
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
        } else {
            LogError("SetShaderMatrix3x2Array: No shader attached");
        }
    }

    void SetShaderMatrix3x3Array(const std::string& name, std::initializer_list<Matrix3x3> mats)
    {
        if (shader_group->current_shader != 0) {
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
        } else {
            LogError("SetShaderMatrix3x3Array: No shader attached");
        }
    }

    void SetShaderMatrix3x4Array(const std::string& name, std::initializer_list<Matrix3x4> mats)
    {
        if (shader_group->current_shader != 0) {
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
            glUniformMatrix3x4fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        } else {
            LogError("SetShaderMatrix3x4Array: No shader attached");
        }
    }

    void SetShaderMatrix4x2Array(const std::string& name, std::initializer_list<Matrix4x2> mats)
    {
        if (shader_group->current_shader != 0) {
            Pointer<float> values = new float[mats.size() * 8];
            int i = 0;
            for (const Matrix4x2& mat : mats) {
                values[i++] = mat[0][0];
                values[i++] = mat[0][1];
                values[i++] = mat[0][2];
                values[i++] = mat[0][3];
                values[i++] = mat[1][0];
                values[i++] = mat[1][1];
                values[i++] = mat[1][2];
                values[i++] = mat[1][3];
            }
            glUniformMatrix4x2fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        } else {
            LogError("SetShaderMatrix4x2Array: No shader attached");
        }
    }

    void SetShaderMatrix4x3Array(const std::string& name, std::initializer_list<Matrix4x3> mats)
    {
        if (shader_group->current_shader != 0) {
            Pointer<float> values = new float[mats.size() * 12];
            int i = 0;
            for (const Matrix4x3& mat : mats) {
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
            }
            glUniformMatrix4x3fv(GetUniformLocation(name), mats.size(), GL_FALSE, values.Raw());
        } else {
            LogError("SetShaderMatrix4x3Array: No shader attached");
        }
    }

    void SetShaderMatrix4x4Array(const std::string& name, std::initializer_list<Matrix4x4> mats)
    {
        if (shader_group->current_shader != 0) {
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
        } else {
            LogError("SetShaderMatrix4x4Array: No shader attached");
        }
    }

    void SetShaderTexture(const std::string& texture, const uint slot)
    {
        if (shader_group->current_shader != 0) {
            glActiveTexture(GL_TEXTURE0 + slot);
            BindTexture(texture);
        } else {
            LogError("SetShaderTexture: No shader attached");
        }
    }

    void SetShaderTexture(const Pointer<Texture>& texture, const uint slot)
    {
        if (shader_group->current_shader != 0) {
            glActiveTexture(GL_TEXTURE0 + slot);
            texture->Bind();
        } else {
            LogError("SetShaderTexture: No shader attached");
        }
    }
}