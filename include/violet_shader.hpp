#ifndef VIOLET_ENGINE_SHADER_HPP
#define VIOLET_ENGINE_SHADER_HPP

namespace Violet
{
    typedef void (*ShaderCallback)(void* user_data);
    
    extern void LoadShader             (const std::string& id, const std::string& vertex_code, const std::string& frag_code);
    extern void DestroyShader          (const std::string& id);
    extern void DestroyAllShaders      ();
    extern void SetShaderFloat         (const std::string& name, const float value);
    extern void SetShaderInt           (const std::string& name, const int value);
    extern void SetShaderUInt          (const std::string& name, const uint value);
    extern void SetShaderVector2       (const std::string& name, const Vector2& vec);
    extern void SetShaderIVector2      (const std::string& name, const IVector2& vec);
    extern void SetShaderUIVector2     (const std::string& name, const UIVector2& vec);
    extern void SetShaderVector3       (const std::string& name, const Vector3& vec);
    extern void SetShaderIVector3      (const std::string& name, const IVector3& vec);
    extern void SetShaderUIVector3     (const std::string& name, const UIVector3& vec);
    extern void SetShaderVector4       (const std::string& name, const Vector4& vec);
    extern void SetShaderIVector4      (const std::string& name, const IVector4& vec);
    extern void SetShaderUIVector4     (const std::string& name, const UIVector4& vec);
    extern void SetShaderFloatArray    (const std::string& name, std::initializer_list<float> values);
    extern void SetShaderIntArray      (const std::string& name, std::initializer_list<int> values);
    extern void SetShaderUIntArray     (const std::string& name, std::initializer_list<uint> values);
    extern void SetShaderVector2Array  (const std::string& name, std::initializer_list<Vector2> vecs);
    extern void SetShaderIVector2Array (const std::string& name, std::initializer_list<IVector2> vecs);
    extern void SetShaderUIVector2Array(const std::string& name, std::initializer_list<UIVector2> vecs);
    extern void SetShaderVector3Array  (const std::string& name, std::initializer_list<Vector3> vecs);
    extern void SetShaderIVector3Array (const std::string& name, std::initializer_list<IVector3> vecs);
    extern void SetShaderUIVector3Array(const std::string& name, std::initializer_list<UIVector3> vecs);
    extern void SetShaderVector4Array  (const std::string& name, std::initializer_list<Vector4> vecs);
    extern void SetShaderIVector4Array (const std::string& name, std::initializer_list<IVector4> vecs);
    extern void SetShaderUIVector4Array(const std::string& name, std::initializer_list<UIVector4> vecs);
    /*extern void SetShaderMatrix2x4     (const std::string& name, const uint count, const float* const value);
    extern void SetShaderMatrix4x2     (const std::string& name, const uint count, const float* const value);
    extern void SetShaderMatrix3x4     (const std::string& name, const uint count, const float* const value);
    extern void SetShaderMatrix4x3     (const std::string& name, const uint count, const float* const value);*/
    extern void SetShaderMatrix2x2(const std::string& name, const Matrix2x2& mat);
    extern void SetShaderMatrix2x3(const std::string& name, const Matrix2x3& mat);
    extern void SetShaderMatrix3x2(const std::string& name, const Matrix3x2& mat);
    extern void SetShaderMatrix3x3(const std::string& name, const Matrix3x3& mat);
    extern void SetShaderMatrix4x4(const std::string& name, const Matrix4x4& mat);
    /*extern void SetShaderMatrix2x4Array(const std::string& name, const uint count, const float* const value);
    extern void SetShaderMatrix4x2Array(const std::string& name, const uint count, const float* const value);
    extern void SetShaderMatrix3x4Array(const std::string& name, const uint count, const float* const value);
    extern void SetShaderMatrix4x3Array(const std::string& name, const uint count, const float* const value);*/
    extern void SetShaderMatrix2x2Array(const std::string& name, std::initializer_list<Matrix2x2> mats);
    extern void SetShaderMatrix2x3Array(const std::string& name, std::initializer_list<Matrix2x3> mats);
    extern void SetShaderMatrix3x2Array(const std::string& name, std::initializer_list<Matrix3x2> mats);
    extern void SetShaderMatrix3x3Array(const std::string& name, std::initializer_list<Matrix3x3> mats);
    extern void SetShaderMatrix4x4Array(const std::string& name, std::initializer_list<Matrix4x4> mats);
    extern void SetShaderTexture       (const std::string& texture, const uint slot);
}

#endif // VIOLET_ENGINE_SHADER_HPP