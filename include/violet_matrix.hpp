#ifndef VIOLET_ENGINE_MATRIX_HPP
#define VIOLET_ENGINE_MATRIX_HPP

namespace Violet
{
    class Matrix2x3;
    class Matrix2x4;
    class Matrix3x2;
    class Matrix3x3;
    class Matrix3x4;
    class Matrix4x2;
    class Matrix4x3;
    class Matrix4x4;

    class Matrix2x2
    {
        public:
            Matrix2x2() { }
            Matrix2x2(const float value);
            Matrix2x2(const float value1, const float value2,
                      const float value3, const float value4);
            Matrix2x2(const float arr[4]);
            Matrix2x2(const Vector2& vec1, const Vector2& vec2);
            Matrix2x2(const Matrix2x2& mat);
            
            Matrix2x2&   operator= (const Matrix2x2& mat);
            Matrix2x2    operator+ (const Matrix2x2& mat) const;
            Matrix2x2    operator- (const Matrix2x2& mat) const;
            Vector2      operator* (const Vector2& vec) const;
            Matrix2x2    operator* (const Matrix2x2& mat) const;
            Matrix2x3    operator* (const Matrix2x3& mat) const;
            Matrix2x4    operator* (const Matrix2x4& mat) const;
            Matrix2x2    operator/ (const Matrix2x2& mat) const;
            Matrix2x2&   operator+=(const Matrix2x2& mat);
            Matrix2x2&   operator-=(const Matrix2x2& mat);
            Matrix2x2&   operator*=(const Matrix2x2& mat);
            Matrix2x2&   operator/=(const Matrix2x2& mat);
            bool         operator==(const Matrix2x2& mat);
            float*       operator[](const size_t index);
            const float* operator[](const size_t index) const;

            static Matrix2x2 Identity();

            float data[2][2]{ { 0 } };
    };

    class Matrix2x3
    {
        public:
            Matrix2x3() { }
            Matrix2x3(const float value);
            Matrix2x3(const float value1, const float value2,
                      const float value3, const float value4,
                      const float value5, const float value6);
            Matrix2x3(const float arr[6]);
            Matrix2x3(const Vector2& vec1, const Vector2& vec2, const Vector2& vec3);
            Matrix2x3(const Matrix2x3& mat);
            
            Matrix2x3&   operator= (const Matrix2x3& mat);
            Matrix2x3    operator+ (const Matrix2x3& mat) const;
            Matrix2x3    operator- (const Matrix2x3& mat) const;
            Vector2      operator* (const Vector3& vec) const;
            Matrix2x2    operator* (const Matrix3x2& mat) const;
            Matrix2x3    operator* (const Matrix3x3& mat) const;
            Matrix2x4    operator* (const Matrix3x4& mat) const;
            Matrix2x3    operator/ (const Matrix2x3& mat) const;
            Matrix2x3&   operator+=(const Matrix2x3& mat);
            Matrix2x3&   operator-=(const Matrix2x3& mat);
            Matrix2x3&   operator*=(const Matrix3x3& mat);
            Matrix2x3&   operator/=(const Matrix2x3& mat);
            bool         operator==(const Matrix2x3& mat);
            float*       operator[](const size_t index);
            const float* operator[](const size_t index) const;

            float data[3][2]{ { 0 } };
    };

    class Matrix2x4
    {
        public:
            Matrix2x4() { }
            Matrix2x4(const float value);
            Matrix2x4(const float value1, const float value2,
                      const float value3, const float value4,
                      const float value5, const float value6,
                      const float value7, const float value8);
            Matrix2x4(const float arr[8]);
            Matrix2x4(const Vector2& vec1, const Vector2& vec2, const Vector2& vec3, const Vector2& vec4);
            Matrix2x4(const Matrix2x4& mat);
            
            Matrix2x4&   operator= (const Matrix2x4& mat);
            Matrix2x4    operator+ (const Matrix2x4& mat) const;
            Matrix2x4    operator- (const Matrix2x4& mat) const;
            Vector2      operator* (const Vector4& vec) const;
            Matrix2x2    operator* (const Matrix4x2& vec) const;
            Matrix2x3    operator* (const Matrix4x3& vec) const;
            Matrix2x4    operator* (const Matrix4x4& vec) const;
            Matrix2x4    operator/ (const Matrix2x4& vec) const;
            Matrix2x4&   operator+=(const Matrix2x4& mat);
            Matrix2x4&   operator-=(const Matrix2x4& mat);
            Matrix2x4&   operator*=(const Matrix4x4& mat);
            Matrix2x4&   operator/=(const Matrix2x4& mat);
            bool         operator==(const Matrix2x4& mat);
            float*       operator[](const size_t index);
            const float* operator[](const size_t index) const;

            float data[4][2]{ { 0 } };
    };

    class Matrix3x2
    {
        public:
            Matrix3x2() { }
            Matrix3x2(const float value);
            Matrix3x2(const float value1, const float value2, const float value3,
                      const float value4, const float value5, const float value6);
            Matrix3x2(const float arr[6]);
            Matrix3x2(const Vector3& vec1, const Vector3& vec2);
            Matrix3x2(const Matrix3x2& mat);
            
            Matrix3x2&   operator= (const Matrix3x2& mat);
            Matrix3x2    operator+ (const Matrix3x2& mat) const;
            Matrix3x2    operator- (const Matrix3x2& mat) const;
            Vector3      operator* (const Vector2& vec) const;
            Matrix3x2    operator* (const Matrix2x2& mat) const;
            Matrix3x3    operator* (const Matrix2x3& mat) const;
            Matrix3x4    operator* (const Matrix2x4& mat) const;
            Matrix3x2    operator/ (const Matrix3x2& mat) const;
            Matrix3x2&   operator+=(const Matrix3x2& mat);
            Matrix3x2&   operator-=(const Matrix3x2& mat);
            Matrix3x2&   operator*=(const Matrix2x2& mat);
            Matrix3x2&   operator/=(const Matrix3x2& mat);
            bool         operator==(const Matrix3x2& mat);
            float*       operator[](const size_t index);
            const float* operator[](const size_t index) const;

            float data[2][3]{ { 0 } };
    };

    class Matrix3x3
    {
        public:
            Matrix3x3() { }
            Matrix3x3(const float value);
            Matrix3x3(const float value1, const float value2, const float value3,
                      const float value4, const float value5, const float value6,
                      const float value7, const float value8, const float value9);
            Matrix3x3(const float arr[9]);
            Matrix3x3(const Vector3& vec1, const Vector3& vec2, const Vector3& vec3);
            Matrix3x3(const Matrix3x3& mat);
            
            Matrix3x3&   operator= (const Matrix3x3& mat);
            Matrix3x3    operator+ (const Matrix3x3& mat) const;
            Matrix3x3    operator- (const Matrix3x3& mat) const;
            Vector3      operator* (const Vector3& vec) const;
            Matrix3x2    operator* (const Matrix3x2& mat) const;
            Matrix3x3    operator* (const Matrix3x3& mat) const;
            Matrix3x4    operator* (const Matrix3x4& mat) const;
            Matrix3x3    operator/ (const Matrix3x3& mat) const;
            Matrix3x3&   operator+=(const Matrix3x3& mat);
            Matrix3x3&   operator-=(const Matrix3x3& mat);
            Matrix3x3&   operator*=(const Matrix3x3& mat);
            Matrix3x3&   operator/=(const Matrix3x3& mat);
            bool         operator==(const Matrix3x3& mat);
            float*       operator[](const size_t index);
            const float* operator[](const size_t index) const;

            static Matrix3x3 Identity();

            float data[3][3]{ { 0 } };
    };

    class Matrix3x4
    {
        public:
            Matrix3x4() { }
            Matrix3x4(const float value);
            Matrix3x4(const float value1,  const float value2,  const float value3,
                      const float value4,  const float value5,  const float value6,
                      const float value7,  const float value8,  const float value9,
                      const float value10, const float value11, const float value12);
            Matrix3x4(const float arr[12]);
            Matrix3x4(const Vector3& vec1, const Vector3& vec2, const Vector3& vec3, const Vector3& vec4);
            Matrix3x4(const Matrix3x4& mat);
            
            Matrix3x4&   operator= (const Matrix3x4& mat);
            Matrix3x4    operator+ (const Matrix3x4& mat) const;
            Matrix3x4    operator- (const Matrix3x4& mat) const;
            Vector3      operator* (const Vector4& vec) const;
            Matrix3x2    operator* (const Matrix4x2& mat) const;
            Matrix3x3    operator* (const Matrix4x3& mat) const;
            Matrix3x4    operator* (const Matrix4x4& mat) const;
            Matrix3x4    operator/ (const Matrix3x4& mat) const;
            Matrix3x4&   operator+=(const Matrix3x4& mat);
            Matrix3x4&   operator-=(const Matrix3x4& mat);
            Matrix3x4&   operator*=(const Matrix4x4& mat);
            Matrix3x4&   operator/=(const Matrix3x4& mat);
            bool         operator==(const Matrix3x4& mat);
            float*       operator[](const size_t index);
            const float* operator[](const size_t index) const;

            float data[4][3]{ { 0 } };
    };

    class Matrix4x2
    {
        public:
            Matrix4x2() { }
            Matrix4x2(const float value);
            Matrix4x2(const float value1,  const float value2,  const float value3,  const float value4,
                      const float value5,  const float value6,  const float value7,  const float value8);
            Matrix4x2(const float arr[8]);
            Matrix4x2(const Vector4& vec1, const Vector4& vec2);
            Matrix4x2(const Matrix4x2& mat);
            
            Matrix4x2&   operator= (const Matrix4x2& mat);
            Matrix4x2    operator+ (const Matrix4x2& mat) const;
            Matrix4x2    operator- (const Matrix4x2& mat) const;
            Vector4      operator* (const Vector2& vec) const;
            Matrix4x2    operator* (const Matrix2x2& mat) const;
            Matrix4x3    operator* (const Matrix2x3& mat) const;
            Matrix4x4    operator* (const Matrix2x4& mat) const;
            Matrix4x2    operator/ (const Matrix4x2& mat) const;
            Matrix4x2&   operator+=(const Matrix4x2& mat);
            Matrix4x2&   operator-=(const Matrix4x2& mat);
            Matrix4x2&   operator*=(const Matrix2x2& mat);
            Matrix4x2&   operator/=(const Matrix4x2& mat);
            bool         operator==(const Matrix4x2& mat);
            float*       operator[](const size_t index);
            const float* operator[](const size_t index) const;

            float data[2][4]{ { 0 } };
    };

    class Matrix4x3
    {
        public:
            Matrix4x3() { }
            Matrix4x3(const float value);
            Matrix4x3(const float value1,  const float value2,  const float value3,  const float value4,
                      const float value5,  const float value6,  const float value7,  const float value8,
                      const float value9,  const float value10, const float value11, const float value12);
            Matrix4x3(const float arr[12]);
            Matrix4x3(const Vector4& vec1, const Vector4& vec2, const Vector4& vec3);
            Matrix4x3(const Matrix4x3& mat);
            
            Matrix4x3&   operator= (const Matrix4x3& mat);
            Matrix4x3    operator+ (const Matrix4x3& mat) const;
            Matrix4x3    operator- (const Matrix4x3& mat) const;
            Vector4      operator* (const Vector3& vec) const;
            Matrix4x2    operator* (const Matrix3x2& mat) const;
            Matrix4x3    operator* (const Matrix3x3& mat) const;
            Matrix4x4    operator* (const Matrix3x4& mat) const;
            Matrix4x3    operator/ (const Matrix4x3& mat) const;
            Matrix4x3&   operator+=(const Matrix4x3& mat);
            Matrix4x3&   operator-=(const Matrix4x3& mat);
            Matrix4x3&   operator*=(const Matrix3x3& mat);
            Matrix4x3&   operator/=(const Matrix4x3& mat);
            bool         operator==(const Matrix4x3& mat);
            float*       operator[](const size_t index);
            const float* operator[](const size_t index) const;

            float data[3][4]{ { 0 } };
    };

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
            Matrix4x4(const Vector4& vec1, const Vector4& vec2, const Vector4& vec3, const Vector4& vec4);
            Matrix4x4(const Matrix4x4& mat);
            
            Matrix4x4&   operator= (const Matrix4x4& mat);
            Matrix4x4    operator+ (const Matrix4x4& mat) const;
            Matrix4x4    operator- (const Matrix4x4& mat) const;
            Vector4      operator* (const Vector4& vec) const;
            Matrix4x2    operator* (const Matrix4x2& mat) const;
            Matrix4x3    operator* (const Matrix4x3& mat) const;
            Matrix4x4    operator* (const Matrix4x4& mat) const;
            Matrix4x4    operator/ (const Matrix4x4& mat) const;
            Matrix4x4&   operator+=(const Matrix4x4& mat);
            Matrix4x4&   operator-=(const Matrix4x4& mat);
            Matrix4x4&   operator*=(const Matrix4x4& mat);
            Matrix4x4&   operator/=(const Matrix4x4& mat);
            bool         operator==(const Matrix4x4& mat);
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