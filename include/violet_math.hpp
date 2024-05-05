#ifndef VIOLET_ENGINE_MATH_HPP
#define VIOLET_ENGINE_MATH_HPP

namespace Violet
{
    class Matrix4x4;

    class Vector2D
    {
        public:
            Vector2D() { }
            Vector2D(const float value);
            Vector2D(const float arr[2]);
            Vector2D(const float x, const float y);
            Vector2D(const Vector2D& vec);

            Vector2D&    operator= (const float value);
            Vector2D&    operator= (const float arr[2]);
            Vector2D&    operator= (const Vector2D& vec);
            Vector2D     operator+ (const float value) const;
            Vector2D     operator+ (const float arr[2]) const;
            Vector2D     operator+ (const Vector2D& vec) const;
            Vector2D     operator- (const float value) const;
            Vector2D     operator- (const float arr[2]) const;
            Vector2D     operator- (const Vector2D& vec) const;
            Vector2D     operator* (const float value) const;
            Vector2D     operator* (const float arr[2]) const;
            Vector2D     operator* (const Vector2D& vec) const;
            Vector2D     operator/ (const float value) const;
            Vector2D     operator/ (const float arr[2]) const;
            Vector2D     operator/ (const Vector2D& vec) const;
            Vector2D&    operator+=(const float value);
            Vector2D&    operator+=(const float arr[2]);
            Vector2D&    operator+=(const Vector2D& vec);
            Vector2D&    operator-=(const float value);
            Vector2D&    operator-=(const float arr[2]);
            Vector2D&    operator-=(const Vector2D& vec);
            Vector2D&    operator*=(const float value);
            Vector2D&    operator*=(const float arr[2]);
            Vector2D&    operator*=(const Vector2D& vec);
            Vector2D&    operator/=(const float value);
            Vector2D&    operator/=(const float arr[2]);
            Vector2D&    operator/=(const Vector2D& vec);
            bool         operator==(const float value);
            bool         operator==(const float arr[2]);
            bool         operator==(const Vector2D& vec);
            float&       operator[](const size_t index);
            const float& operator[](const size_t index) const;

            float&       X();
            const float& X() const;
            float&       Y();
            const float& Y() const;
            
            float    Dot      (const Vector2D& vec) const;
            float    Length   () const;
            Vector2D Normalize() const;
            float    Distance (const Vector2D& vec) const;

            float data[2]{ { 0 } };
    };

    class Vector3D
    {
        public:
            Vector3D() { }
            Vector3D(const float value);
            Vector3D(const float arr[3]);
            Vector3D(const float x, const float y, const float z);
            Vector3D(const Vector2D& vec, const float z);
            Vector3D(const Vector3D& vec);

            Vector3D&    operator= (const float value);
            Vector3D&    operator= (const float arr[3]);
            Vector3D&    operator= (const Vector3D& vec);
            Vector3D     operator+ (const float value) const;
            Vector3D     operator+ (const float arr[3]) const;
            Vector3D     operator+ (const Vector3D& vec) const;
            Vector3D     operator- (const float value) const;
            Vector3D     operator- (const float arr[3]) const;
            Vector3D     operator- (const Vector3D& vec) const;
            Vector3D     operator* (const float value) const;
            Vector3D     operator* (const float arr[3]) const;
            Vector3D     operator* (const Vector3D& vec) const;
            Vector3D     operator/ (const float value) const;
            Vector3D     operator/ (const float arr[3]) const;
            Vector3D     operator/ (const Vector3D& vec) const;
            Vector3D&    operator+=(const float value);
            Vector3D&    operator+=(const float arr[3]);
            Vector3D&    operator+=(const Vector3D& vec);
            Vector3D&    operator-=(const float value);
            Vector3D&    operator-=(const float arr[3]);
            Vector3D&    operator-=(const Vector3D& vec);
            Vector3D&    operator*=(const float value);
            Vector3D&    operator*=(const float arr[3]);
            Vector3D&    operator*=(const Vector3D& vec);
            Vector3D&    operator/=(const float value);
            Vector3D&    operator/=(const float arr[3]);
            Vector3D&    operator/=(const Vector3D& vec);
            bool         operator==(const float value);
            bool         operator==(const float arr[3]);
            bool         operator==(const Vector3D& vec);
            float&       operator[](const size_t index);
            const float& operator[](const size_t index) const;

            float&       X();
            const float& X() const;
            float&       Y();
            const float& Y() const;
            float&       Z();
            const float& Z() const;
            
            float    Dot      (const Vector3D& vec) const;
            Vector3D Cross    (const Vector3D& vec) const;
            float    Length   () const;
            Vector3D Normalize() const;
            float    Distance (const Vector3D& vec) const;

            float data[3]{ { 0 } };
    };

    class Vector4D
    {
        public:
            Vector4D() { }
            Vector4D(const float value);
            Vector4D(const float arr[4]);
            Vector4D(const float x, const float y, const float z, const float w);
            Vector4D(const Vector2D& vec, const float z, const float w);
            Vector4D(const Vector3D& vec, const float w);
            Vector4D(const Vector4D& vec);

            Vector4D&    operator= (const float value);
            Vector4D&    operator= (const float arr[4]);
            Vector4D&    operator= (const Vector4D& vec);
            Vector4D     operator+ (const float value) const;
            Vector4D     operator+ (const float arr[4]) const;
            Vector4D     operator+ (const Vector4D& vec)const;
            Vector4D     operator- (const float value) const;
            Vector4D     operator- (const float arr[4]) const;
            Vector4D     operator- (const Vector4D& vec) const;
            Vector4D     operator* (const float value) const;
            Vector4D     operator* (const float arr[4]) const;
            Vector4D     operator* (const Vector4D& vec) const;
            Vector4D     operator* (const Matrix4x4& vec) const;
            Vector4D     operator/ (const float value) const;
            Vector4D     operator/ (const float arr[4]) const;
            Vector4D     operator/ (const Vector4D& vec) const;
            Vector4D&    operator+=(const float value);
            Vector4D&    operator+=(const float arr[4]);
            Vector4D&    operator+=(const Vector4D& vec);
            Vector4D&    operator-=(const float value);
            Vector4D&    operator-=(const float arr[4]);
            Vector4D&    operator-=(const Vector4D& vec);
            Vector4D&    operator*=(const float value);
            Vector4D&    operator*=(const float arr[4]);
            Vector4D&    operator*=(const Vector4D& vec);
            Vector4D&    operator*=(const Matrix4x4& vec);
            Vector4D&    operator/=(const float value);
            Vector4D&    operator/=(const float arr[4]);
            Vector4D&    operator/=(const Vector4D& vec);
            bool         operator==(const float value);
            bool         operator==(const float arr[4]);
            bool         operator==(const Vector4D& vec);
            float&       operator[](const size_t index);
            const float& operator[](const size_t index) const;

            float&       X();
            const float& X() const;
            float&       Y();
            const float& Y() const;
            float&       Z();
            const float& Z() const;
            float&       W();
            const float& W() const;

            float    Dot      (const Vector4D& vec) const;
            float    Length   () const;
            Vector4D Normalize() const;
            float    Distance (const Vector4D& vec) const;

            float data[4]{ { 0 } };
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
            Matrix4x4(const Vector4D& vec1, const Vector4D& vec2, const Vector4D& vec3, const Vector4D& vec4);
            Matrix4x4(const Matrix4x4& mat);
            
            Matrix4x4& operator= (const float value);
            Matrix4x4& operator= (const Matrix4x4& mat);
            Matrix4x4  operator+ (const Matrix4x4& mat) const;
            Matrix4x4  operator- (const Matrix4x4& mat) const;
            Vector4D   operator* (const Vector4D& vec) const;
            Matrix4x4  operator* (const Matrix4x4& mat) const;
            Matrix4x4& operator+=(const Matrix4x4& mat);
            Matrix4x4& operator-=(const Matrix4x4& mat);
            Matrix4x4& operator*=(const Matrix4x4& mat);

            static Matrix4x4 Identity();

            float data[16]{ { 0 } };
    };

    extern Matrix4x4 OrthoMatrix          (const Vector2D& x, const Vector2D& y, const Vector2D& z);
    extern Matrix4x4 OrthoMatrix          (const Vector2D& x, const Vector2D& y);
    extern Matrix4x4 TranslateMatrix      (const Vector3D& vec);
    extern Matrix4x4 TranslateMatrix      (const Vector2D& vec);
    extern Matrix4x4 RotateXMatrix        (const float angle);
    extern Matrix4x4 RotateYMatrix        (const float angle);
    extern Matrix4x4 RotateZMatrix        (const float angle);
    extern Matrix4x4 RotateMatrix         (const Vector3D& vec);
    extern Matrix4x4 ScaleMatrix          (const Vector3D& vec);
    extern Matrix4x4 ScaleMatrix          (const Vector2D& vec);
    extern Matrix4x4 TransformMatrix      (const Vector3D& translate, const Vector3D& rotate, const Vector3D& scale);
    extern Matrix4x4 TransformMatrix      (const Vector2D& translate, const float rotate, const Vector2D& scale);

    namespace Math
    {
        constexpr float Pi = 3.14159265358979323846f;

        extern float  Sin       (const float angle);
        extern double Sin       (const double angle);
        extern float  Cos       (const float angle);
        extern double Cos       (const double angle);
        extern float  SinDegrees(const float angle);
        extern double SinDegrees(const double angle);
        extern float  CosDegrees(const float angle);
        extern double CosDegrees(const double angle);
        extern float  Radians   (const float degrees);
        extern double Radians   (const double degrees);
        extern float  Degrees   (const float radians);
        extern double Degrees   (const double radians);
    }
}

#endif // VIOLET_ENGINE_MATH_HPP