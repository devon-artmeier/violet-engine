#ifndef VIOLET_ENGINE_MATH_HPP
#define VIOLET_ENGINE_MATH_HPP

namespace Violet
{
    class Vector2D
    {
        public:
            Vector2D() { }
            Vector2D(const float value);
            Vector2D(const float x, const float y);
            Vector2D(const Vector2D& other);

            Vector2D&    operator= (const float value);
            Vector2D&    operator= (const Vector2D& other);
            Vector2D     operator+ (const float value) const;
            Vector2D     operator+ (const Vector2D& other) const;
            Vector2D     operator- (const float value) const;
            Vector2D     operator- (const Vector2D& other) const;
            Vector2D     operator* (const float value) const;
            Vector2D     operator* (const Vector2D& other) const;
            Vector2D     operator/ (const float value) const;
            Vector2D     operator/ (const Vector2D& other) const;
            Vector2D&    operator+=(const float value);
            Vector2D&    operator+=(const Vector2D& other);
            Vector2D&    operator-=(const float value);
            Vector2D&    operator-=(const Vector2D& other);
            Vector2D&    operator*=(const float value);
            Vector2D&    operator*=(const Vector2D& other);
            Vector2D&    operator/=(const float value);
            Vector2D&    operator/=(const Vector2D& other);
            float&       operator[](const size_t index);
            const float& operator[](const size_t index) const;

            float&       X();
            const float& X() const;
            float&       Y();
            const float& Y() const;
            
            float*   Linear   ();
            float    Dot      (const Vector2D& other) const;
            float    Length   () const;
            Vector2D Normalize() const;
            float    Distance (const Vector2D& other) const;

        private:
            float data[2]{ { 0 } };
    };

    class Vector3D
    {
        public:
            Vector3D() { }
            Vector3D(const float value);
            Vector3D(const float x, const float y, const float z);
            Vector3D(const Vector2D& other, const float z);
            Vector3D(const Vector3D& other);

            Vector3D&    operator= (const float value);
            Vector3D&    operator= (const Vector3D& other);
            Vector3D     operator+ (const float value) const;
            Vector3D     operator+ (const Vector3D& other) const;
            Vector3D     operator- (const float value) const;
            Vector3D     operator- (const Vector3D& other) const;
            Vector3D     operator* (const float value) const;
            Vector3D     operator* (const Vector3D& other) const;
            Vector3D     operator/ (const float value) const;
            Vector3D     operator/ (const Vector3D& other) const;
            Vector3D&    operator+=(const float value);
            Vector3D&    operator+=(const Vector3D& other);
            Vector3D&    operator-=(const float value);
            Vector3D&    operator-=(const Vector3D& other);
            Vector3D&    operator*=(const float value);
            Vector3D&    operator*=(const Vector3D& other);
            Vector3D&    operator/=(const float value);
            Vector3D&    operator/=(const Vector3D& other);
            float&       operator[](const size_t index);
            const float& operator[](const size_t index) const;

            float&       X();
            const float& X() const;
            float&       Y();
            const float& Y() const;
            float&       Z();
            const float& Z() const;
            
            float*   Linear   ();
            float    Dot      (const Vector3D& other) const;
            Vector3D Cross    (const Vector3D& other) const;
            float    Length   () const;
            Vector3D Normalize() const;
            float    Distance (const Vector3D& other) const;

        private:
            float data[3]{ { 0 } };
    };

    class Vector4D
    {
        public:
            Vector4D() { }
            Vector4D(const float value);
            Vector4D(const float x, const float y, const float z, const float w);
            Vector4D(const Vector2D& other, const float z, const float w);
            Vector4D(const Vector3D& other, const float w);
            Vector4D(const Vector4D& other);

            Vector4D&    operator= (const float value);
            Vector4D&    operator= (const Vector4D& other);
            Vector4D     operator+ (const float value) const;
            Vector4D     operator+ (const Vector4D& other)const;
            Vector4D     operator- (const float value) const;
            Vector4D     operator- (const Vector4D& other) const;
            Vector4D     operator* (const float value) const;
            Vector4D     operator* (const Vector4D& other) const;
            Vector4D     operator/ (const float value) const;
            Vector4D     operator/ (const Vector4D& other) const;
            Vector4D&    operator+=(const float value);
            Vector4D&    operator+=(const Vector4D& other);
            Vector4D&    operator-=(const float value);
            Vector4D&    operator-=(const Vector4D& other);
            Vector4D&    operator*=(const float value);
            Vector4D&    operator*=(const Vector4D& other);
            Vector4D&    operator/=(const float value);
            Vector4D&    operator/=(const Vector4D& other);
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

            float*   Linear   ();
            float    Dot      (const Vector4D& other) const;
            float    Length   () const;
            Vector4D Normalize() const;
            float    Distance (const Vector4D& other) const;

        private:
            float data[4]{ { 0 } };
    };

    class Matrix4x4
    {
        public:
            Matrix4x4() { }
            Matrix4x4(const float value);
            Matrix4x4(const Vector4D& data1, const Vector4D& data2, const Vector4D& data3, const Vector4D& data4);
            Matrix4x4(const Matrix4x4& other);

            Vector4D        operator* (const Vector4D& other) const;
            Matrix4x4       operator* (const Matrix4x4& other) const;
            Vector4D&       operator[](const size_t index);
            const Vector4D& operator[](const size_t index) const;

        private:
            Vector4D data[4]{ { 0 } };
    };

    namespace Math
    {
        constexpr double Pi = 3.14159265358979323846;

        extern float  Sin     (const float angle);
        extern double Sin     (const double angle);
        extern float  Cos     (const float angle);
        extern double Cos     (const double angle);
        extern float  SinDeg  (const float angle);
        extern double SinDeg  (const double angle);
        extern float  CosDeg  (const float angle);
        extern double CosDeg  (const double angle);
        extern float  DegToRad(const float degrees);
        extern double DegToRad(const double degrees);
        extern float  RadToDeg(const float radians);
        extern double RadToDeg(const double radians);
    }
}

#endif // VIOLET_ENGINE_MATH_HPP