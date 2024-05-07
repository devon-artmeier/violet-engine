#ifndef VIOLET_ENGINE_MATRIX_HPP
#define VIOLET_ENGINE_MATRIX_HPP

namespace Violet
{
    class Matrix4x4
    {
        public:
            Matrix4x4() { }
            Matrix4x4(const float value);
            Matrix4x4(const float value1,  const float value2,  const float value3,  const float value4,
                      const float value5,  const float value6,  const float value7,  const float value8,
                      const float value9,  const float value10, const float value11, const float value12,
                      const float value13, const float value14, const float value15, const float value16);
            Matrix4x4(const float arr[16]);
            Matrix4x4(const float arr1[4], const float arr2[4], const float arr3[4], const float arr4[4]);
            Matrix4x4(const Vector4& vec1, const Vector4& vec2, const Vector4& vec3, const Vector4& vec4);
            Matrix4x4(const Matrix4x4& mat);
            
            Matrix4x4&   operator= (const float value);
            Matrix4x4&   operator= (const Matrix4x4& mat);
            Matrix4x4    operator+ (const Matrix4x4& mat) const;
            Matrix4x4    operator- (const Matrix4x4& mat) const;
            Vector4      operator* (const Vector4& vec) const;
            Matrix4x4    operator* (const Matrix4x4& mat) const;
            Matrix4x4&   operator+=(const Matrix4x4& mat);
            Matrix4x4&   operator-=(const Matrix4x4& mat);
            Matrix4x4&   operator*=(const Matrix4x4& mat);
            float*       operator[](const size_t index);
            const float* operator[](const size_t index) const;

            static Matrix4x4 Identity();

            float data[4][4]{ { 0 } };
    };

    extern Matrix4x4 OrthoMatrix    (const Vector2& x, const Vector2& y, const Vector2& z);
    extern Matrix4x4 OrthoMatrix    (const Vector2& x, const Vector2& y);
    extern Matrix4x4 TranslateMatrix(const Vector3& vec);
    extern Matrix4x4 TranslateMatrix(const Vector2& vec);
    extern Matrix4x4 RotateXMatrix  (const float angle);
    extern Matrix4x4 RotateYMatrix  (const float angle);
    extern Matrix4x4 RotateZMatrix  (const float angle);
    extern Matrix4x4 RotateMatrix   (const Vector3& vec);
    extern Matrix4x4 ScaleMatrix    (const Vector3& vec);
    extern Matrix4x4 ScaleMatrix    (const Vector2& vec);
    extern Matrix4x4 TransformMatrix(const Vector3& translate, const Vector3& rotate, const Vector3& scale);
    extern Matrix4x4 TransformMatrix(const Vector2& translate, const float rotate, const Vector2& scale);
}

#endif // VIOLET_ENGINE_MATRIX_HPP