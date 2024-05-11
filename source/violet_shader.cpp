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

        char        log1[512], log2[512], log3[512];
        int         success1, success2, success3;

        const char* vertex_code_c = vertex_code.c_str();
        const char* frag_code_c   = frag_code.c_str();

        LogInfo(this->id + ": Compiling vertex shader");

        uint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_code_c, nullptr);
        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success1);
        glGetShaderInfoLog(vertex_shader, 512, nullptr, log1);

        LogInfo(this->id + ": Compiling fragment shader");

        uint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag_shader, 1, &frag_code_c, nullptr);
        glCompileShader(frag_shader);
        glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success2);
        glGetShaderInfoLog(frag_shader, 512, nullptr, log2);

        LogInfo(this->id + ": Linking shaders");

        this->program = glCreateProgram();
        glAttachShader(this->program, vertex_shader);
        glAttachShader(this->program, frag_shader);
        glLinkProgram(this->program);
        glGetProgramiv(this->program, GL_LINK_STATUS, &success3);
        glGetProgramInfoLog(this->program, 512, nullptr, log3);
        glDeleteShader(vertex_shader);
        glDeleteShader(frag_shader);

        Assert(success1 != 0, this->id + ": Failed to compile vertex shader:\n" + log1);
        Assert(success2 != 0, this->id + ": Failed to compile fragment shader:\n" + log2);
        if (Assert(success3 != 0, this->id + ": Failed to link shaders:\n" + log3)) {
            LogInfo(this->id + ": Compiled successfully");
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

        LogInfo(this->id + ": Destroyed");
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
        }
    }

    void DestroyShader(const std::string& id)
    {
        const Pointer<Shader>& shader = GetShader(id);
        if (shader != nullptr) {
            shader_group->shaders.erase(id);
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
        if (Assert(shader_group->current_shader != 0, "Tried to set float when no shader is attached")) {
            glUniform1f(GetUniformLocation(name), value);
        }
    }
    
    void SetShaderInt(const std::string& name, const int value)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set integer when no shader is attached")) {
            glUniform1i(GetUniformLocation(name), value);
        }
    }
    
    void SetShaderUInt(const std::string& name, const uint value)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set unsigned integer when no shader is attached")) {
            glUniform1ui(GetUniformLocation(name), value);
        }
    }
    
    void SetShaderVector2(const std::string& name, const Vector2& vec)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 2D vector when no shader is attached")) {
            glUniform2f(GetUniformLocation(name), vec[0], vec[1]);
        }
    }
    
    void SetShaderIVector2(const std::string& name, const IVector2& vec)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 2D integer vector when no shader is attached")) {
            glUniform2i(GetUniformLocation(name), vec[0], vec[1]);
        }
    }
    
    void SetShaderUIVector2(const std::string& name, const UIVector2& vec)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 2D unsigned integer vector when no shader is attached")) {
            glUniform2ui(GetUniformLocation(name), vec[0], vec[1]);
        }
    }
    
    void SetShaderVector3(const std::string& name, const Vector3& vec)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 3D vector when no shader is attached")) {
            glUniform3f(GetUniformLocation(name), vec[0], vec[1], vec[2]);
        }
    }
    
    void SetShaderIVector3(const std::string& name, const IVector3& vec)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 3D integer vector when no shader is attached")) {
            glUniform3i(GetUniformLocation(name), vec[0], vec[1], vec[2]);
        }
    }
    
    void SetShaderUIVector3(const std::string& name, const UIVector3& vec)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 3D unsigned integer vector when no shader is attached")) {
            glUniform3ui(GetUniformLocation(name), vec[0], vec[1], vec[2]);
        }
    }
    
    void SetShaderVector4(const std::string& name, const Vector4& vec)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 4D vector when no shader is attached")) {
            glUniform4f(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
        }
    }
    
    void SetShaderIVector4(const std::string& name, const IVector4& vec)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 4D integer vector when no shader is attached")) {
            glUniform4i(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
        }
    }
    
    void SetShaderUIVector4(const std::string& name, const UIVector4& vec)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 4D unsigned integer vector when no shader is attached")) {
            glUniform4ui(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
        }
    }
    
    void SetShaderFloatArray(const std::string& name, std::initializer_list<float> values)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set float array when no shader is attached")) {
            glUniform1fv(GetUniformLocation(name), values.size(), values.begin());
        }
    }
    
    void SetShaderIntArray(const std::string& name, std::initializer_list<int> values)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set integer array when no shader is attached")) {
            glUniform1iv(GetUniformLocation(name), values.size(), values.begin());
        }
    }
    
    void SetShaderUIntArray(const std::string& name, std::initializer_list<uint> values)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set unsigned integer array when no shader is attached")) {
            glUniform1uiv(GetUniformLocation(name), values.size(), values.begin());
        }
    }
    
    void SetShaderVector2Array(const std::string& name, std::initializer_list<Vector2> vecs)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 2D vector array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 2D integer vector array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 2D unsigned integer vector array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 3D vector array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 3D integer vector array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 3D unsigned integer vector array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 4D vector array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 4D integer vector array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 4D unsigned integer vector array when no shader is attached")) {
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

    void SetShaderMatrix2x2(const std::string& name, const Matrix2x2& mat)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 2x2 matrix when no shader is attached")) {
            glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        }
    }

    void SetShaderMatrix2x3(const std::string& name, const Matrix2x3& mat)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 2x3 matrix when no shader is attached")) {
            glUniformMatrix2x3fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        }
    }

    void SetShaderMatrix2x4(const std::string& name, const Matrix2x4& mat)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 2x4 matrix when no shader is attached")) {
            glUniformMatrix2x4fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        }
    }

    void SetShaderMatrix3x2(const std::string& name, const Matrix3x2& mat)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 3x2 matrix when no shader is attached")) {
            glUniformMatrix3x2fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        }
    }

    void SetShaderMatrix3x3(const std::string& name, const Matrix3x3& mat)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 3x3 matrix when no shader is attached")) {
            glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        }
    }

    void SetShaderMatrix3x4(const std::string& name, const Matrix3x4& mat)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 3x4 matrix when no shader is attached")) {
            glUniformMatrix3x4fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        }
    }

    void SetShaderMatrix4x2(const std::string& name, const Matrix4x2& mat)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 4x2 matrix when no shader is attached")) {
            glUniformMatrix4x2fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        }
    }

    void SetShaderMatrix4x3(const std::string& name, const Matrix4x3& mat)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 4x3 matrix when no shader is attached")) {
            glUniformMatrix4x3fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        }
    }

    void SetShaderMatrix4x4(const std::string& name, const Matrix4x4& mat)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 4x4 matrix when no shader is attached")) {
            glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, reinterpret_cast<const float*>(mat.data));
        }
    }

    void SetShaderMatrix2x2Array(const std::string& name, std::initializer_list<Matrix2x2> mats)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 2x2 matrix array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 2x3 matrix array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 2x4 matrix array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 3x2 matrix array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 3x3 matrix array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set 3x4 matrix array when no shader is attached")) {
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
        }
    }

    void SetShaderMatrix4x2Array(const std::string& name, std::initializer_list<Matrix4x2> mats)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 4x2 matrix array when no shader is attached")) {
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
        }
    }

    void SetShaderMatrix4x3Array(const std::string& name, std::initializer_list<Matrix4x3> mats)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 4x3 matrix array when no shader is attached")) {
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
        }
    }

    void SetShaderMatrix4x4Array(const std::string& name, std::initializer_list<Matrix4x4> mats)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set 4x4 matrix array when no shader is attached")) {
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
        if (Assert(shader_group->current_shader != 0, "Tried to set texture when no shader is attached")) {
            glActiveTexture(GL_TEXTURE0 + slot);
            BindTexture(texture);
        }
    }

    void SetShaderTexture(const Pointer<Texture>& texture, const uint slot)
    {
        if (Assert(shader_group->current_shader != 0, "Tried to set texture when no shader is attached")) {
            glActiveTexture(GL_TEXTURE0 + slot);
            texture->Bind();
        }
    }
}