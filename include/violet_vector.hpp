#ifndef VIOLET_ENGINE_VECTOR_HPP
#define VIOLET_ENGINE_VECTOR_HPP

namespace Violet
{
    class IVector2;
    class UIVector2;

    class Vector2
    {
        public:
            Vector2() { }
            Vector2(const float value);
            Vector2(const float arr[2]);
            Vector2(const float x, const float y);
            Vector2(const Vector2& vec);

            operator IVector2 () const;
            operator UIVector2() const;

            Vector2&     operator= (const float value);
            Vector2&     operator= (const float arr[2]);
            Vector2&     operator= (const Vector2& vec);
            Vector2      operator+ (const float value) const;
            Vector2      operator+ (const float arr[2]) const;
            Vector2      operator+ (const Vector2& vec) const;
            Vector2      operator- (const float value) const;
            Vector2      operator- (const float arr[2]) const;
            Vector2      operator- (const Vector2& vec) const;
            Vector2      operator* (const float value) const;
            Vector2      operator* (const float arr[2]) const;
            Vector2      operator* (const Vector2& vec) const;
            Vector2      operator/ (const float value) const;
            Vector2      operator/ (const float arr[2]) const;
            Vector2      operator/ (const Vector2& vec) const;
            Vector2&     operator+=(const float value);
            Vector2&     operator+=(const float arr[2]);
            Vector2&     operator+=(const Vector2& vec);
            Vector2&     operator-=(const float value);
            Vector2&     operator-=(const float arr[2]);
            Vector2&     operator-=(const Vector2& vec);
            Vector2&     operator*=(const float value);
            Vector2&     operator*=(const float arr[2]);
            Vector2&     operator*=(const Vector2& vec);
            Vector2&     operator/=(const float value);
            Vector2&     operator/=(const float arr[2]);
            Vector2&     operator/=(const Vector2& vec);
            bool         operator==(const float value);
            bool         operator==(const float arr[2]);
            bool         operator==(const Vector2& vec);
            float&       operator[](const size_t index);
            const float& operator[](const size_t index) const;

            float&       X();
            const float& X() const;
            float&       Y();
            const float& Y() const;
            
            float   Dot      (const Vector2& vec) const;
            float   Length   () const;
            Vector2 Normalize() const;
            float   Distance (const Vector2& vec) const;

            float data[2]{ { 0 } };
    };

    class IVector3;
    class UIVector3;

    class Vector3
    {
        public:
            Vector3() { }
            Vector3(const float value);
            Vector3(const float arr[3]);
            Vector3(const float x, const float y, const float z);
            Vector3(const Vector2& vec, const float z);
            Vector3(const Vector3& vec);

            operator IVector3 () const;
            operator UIVector3() const;

            Vector3&     operator= (const float value);
            Vector3&     operator= (const float arr[3]);
            Vector3&     operator= (const Vector3& vec);
            Vector3      operator+ (const float value) const;
            Vector3      operator+ (const float arr[3]) const;
            Vector3      operator+ (const Vector3& vec) const;
            Vector3      operator- (const float value) const;
            Vector3      operator- (const float arr[3]) const;
            Vector3      operator- (const Vector3& vec) const;
            Vector3      operator* (const float value) const;
            Vector3      operator* (const float arr[3]) const;
            Vector3      operator* (const Vector3& vec) const;
            Vector3      operator/ (const float value) const;
            Vector3      operator/ (const float arr[3]) const;
            Vector3      operator/ (const Vector3& vec) const;
            Vector3&     operator+=(const float value);
            Vector3&     operator+=(const float arr[3]);
            Vector3&     operator+=(const Vector3& vec);
            Vector3&     operator-=(const float value);
            Vector3&     operator-=(const float arr[3]);
            Vector3&     operator-=(const Vector3& vec);
            Vector3&     operator*=(const float value);
            Vector3&     operator*=(const float arr[3]);
            Vector3&     operator*=(const Vector3& vec);
            Vector3&     operator/=(const float value);
            Vector3&     operator/=(const float arr[3]);
            Vector3&     operator/=(const Vector3& vec);
            bool         operator==(const float value);
            bool         operator==(const float arr[3]);
            bool         operator==(const Vector3& vec);
            float&       operator[](const size_t index);
            const float& operator[](const size_t index) const;

            float&       X();
            const float& X() const;
            float&       Y();
            const float& Y() const;
            float&       Z();
            const float& Z() const;
            
            float   Dot      (const Vector3& vec) const;
            Vector3 Cross    (const Vector3& vec) const;
            float   Length   () const;
            Vector3 Normalize() const;
            float   Distance (const Vector3& vec) const;

            float data[3]{ { 0 } };
    };

    class IVector4;
    class UIVector4;
    class Matrix4x4;

    class Vector4
    {
        public:
            Vector4() { }
            Vector4(const float value);
            Vector4(const float arr[4]);
            Vector4(const float x, const float y, const float z, const float w);
            Vector4(const Vector2& vec, const float z, const float w);
            Vector4(const Vector3& vec, const float w);
            Vector4(const Vector4& vec);

            operator IVector4 () const;
            operator UIVector4() const;

            Vector4&     operator= (const float value);
            Vector4&     operator= (const float arr[4]);
            Vector4&     operator= (const Vector4& vec);
            Vector4      operator+ (const float value) const;
            Vector4      operator+ (const float arr[4]) const;
            Vector4      operator+ (const Vector4& vec) const;
            Vector4      operator- (const float value) const;
            Vector4      operator- (const float arr[4]) const;
            Vector4      operator- (const Vector4& vec) const;
            Vector4      operator* (const float value) const;
            Vector4      operator* (const float arr[4]) const;
            Vector4      operator* (const Vector4& vec) const;
            Vector4      operator* (const Matrix4x4& mat) const;
            Vector4      operator/ (const float value) const;
            Vector4      operator/ (const float arr[4]) const;
            Vector4      operator/ (const Vector4& vec) const;
            Vector4&     operator+=(const float value);
            Vector4&     operator+=(const float arr[4]);
            Vector4&     operator+=(const Vector4& vec);
            Vector4&     operator-=(const float value);
            Vector4&     operator-=(const float arr[4]);
            Vector4&     operator-=(const Vector4& vec);
            Vector4&     operator*=(const float value);
            Vector4&     operator*=(const float arr[4]);
            Vector4&     operator*=(const Vector4& vec);
            Vector4&     operator*=(const Matrix4x4& mat);
            Vector4&     operator/=(const float value);
            Vector4&     operator/=(const float arr[4]);
            Vector4&     operator/=(const Vector4& vec);
            bool         operator==(const float value);
            bool         operator==(const float arr[4]);
            bool         operator==(const Vector4& vec);
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

            float   Dot      (const Vector4& vec) const;
            float   Length   () const;
            Vector4 Normalize() const;
            float   Distance (const Vector4& vec) const;

            float data[4]{ { 0 } };
    };

    class IVector2
    {
        public:
            IVector2() { }
            IVector2(const int value);
            IVector2(const int arr[2]);
            IVector2(const int x, const int y);
            IVector2(const IVector2& vec);

            operator Vector2  () const;
            operator UIVector2() const;

            IVector2&  operator= (const int value);
            IVector2&  operator= (const int arr[2]);
            IVector2&  operator= (const IVector2& vec);
            IVector2   operator+ (const int value) const;
            IVector2   operator+ (const int arr[2]) const;
            IVector2   operator+ (const IVector2& vec) const;
            IVector2   operator- (const int value) const;
            IVector2   operator- (const int arr[2]) const;
            IVector2   operator- (const IVector2& vec) const;
            IVector2   operator* (const int value) const;
            IVector2   operator* (const int arr[2]) const;
            IVector2   operator* (const IVector2& vec) const;
            IVector2   operator/ (const int value) const;
            IVector2   operator/ (const int arr[2]) const;
            IVector2   operator/ (const IVector2& vec) const;
            IVector2&  operator+=(const int value);
            IVector2&  operator+=(const int arr[2]);
            IVector2&  operator+=(const IVector2& vec);
            IVector2&  operator-=(const int value);
            IVector2&  operator-=(const int arr[2]);
            IVector2&  operator-=(const IVector2& vec);
            IVector2&  operator*=(const int value);
            IVector2&  operator*=(const int arr[2]);
            IVector2&  operator*=(const IVector2& vec);
            IVector2&  operator/=(const int value);
            IVector2&  operator/=(const int arr[2]);
            IVector2&  operator/=(const IVector2& vec);
            bool       operator==(const int value);
            bool       operator==(const int arr[2]);
            bool       operator==(const IVector2& vec);
            int&       operator[](const size_t index);
            const int& operator[](const size_t index) const;

            int&       X();
            const int& X() const;
            int&       Y();
            const int& Y() const;
            
            int     Dot      (const IVector2& vec) const;
            float   Length   () const;
            Vector2 Normalize() const;
            float   Distance (const IVector2& vec) const;

            int data[2]{ { 0 } };
    };

    class IVector3
    {
        public:
            IVector3() { }
            IVector3(const int value);
            IVector3(const int arr[3]);
            IVector3(const int x, const int y, const int z);
            IVector3(const IVector2& vec, const int z);
            IVector3(const IVector3& vec);

            operator Vector3  () const;
            operator UIVector3() const;

            IVector3&  operator= (const int value);
            IVector3&  operator= (const int arr[3]);
            IVector3&  operator= (const IVector3& vec);
            IVector3   operator+ (const int value) const;
            IVector3   operator+ (const int arr[3]) const;
            IVector3   operator+ (const IVector3& vec) const;
            IVector3   operator- (const int value) const;
            IVector3   operator- (const int arr[3]) const;
            IVector3   operator- (const IVector3& vec) const;
            IVector3   operator* (const int value) const;
            IVector3   operator* (const int arr[3]) const;
            IVector3   operator* (const IVector3& vec) const;
            IVector3   operator/ (const int value) const;
            IVector3   operator/ (const int arr[3]) const;
            IVector3   operator/ (const IVector3& vec) const;
            IVector3&  operator+=(const int value);
            IVector3&  operator+=(const int arr[3]);
            IVector3&  operator+=(const IVector3& vec);
            IVector3&  operator-=(const int value);
            IVector3&  operator-=(const int arr[3]);
            IVector3&  operator-=(const IVector3& vec);
            IVector3&  operator*=(const int value);
            IVector3&  operator*=(const int arr[3]);
            IVector3&  operator*=(const IVector3& vec);
            IVector3&  operator/=(const int value);
            IVector3&  operator/=(const int arr[3]);
            IVector3&  operator/=(const IVector3& vec);
            bool       operator==(const int value);
            bool       operator==(const int arr[3]);
            bool       operator==(const IVector3& vec);
            int&       operator[](const size_t index);
            const int& operator[](const size_t index) const;

            int&       X();
            const int& X() const;
            int&       Y();
            const int& Y() const;
            int&       Z();
            const int& Z() const;
            
            int      Dot      (const IVector3& vec) const;
            IVector3 Cross    (const IVector3& vec) const;
            float    Length   () const;
            Vector3  Normalize() const;
            float    Distance (const IVector3& vec) const;

            int data[3]{ { 0 } };
    };

    class IVector4
    {
        public:
            IVector4() { }
            IVector4(const int value);
            IVector4(const int arr[4]);
            IVector4(const int x, const int y, const int z, const int w);
            IVector4(const IVector2& vec, const int z, const int w);
            IVector4(const IVector3& vec, const int w);
            IVector4(const IVector4& vec);

            operator Vector4  () const;
            operator UIVector4() const;

            IVector4&  operator= (const int value);
            IVector4&  operator= (const int arr[4]);
            IVector4&  operator= (const IVector4& vec);
            IVector4   operator+ (const int value) const;
            IVector4   operator+ (const int arr[4]) const;
            IVector4   operator+ (const IVector4& vec) const;
            IVector4   operator- (const int value) const;
            IVector4   operator- (const int arr[4]) const;
            IVector4   operator- (const IVector4& vec) const;
            IVector4   operator* (const int value) const;
            IVector4   operator* (const int arr[4]) const;
            IVector4   operator* (const IVector4& vec) const;
            IVector4   operator* (const Matrix4x4& mat) const;
            IVector4   operator/ (const int value) const;
            IVector4   operator/ (const int arr[4]) const;
            IVector4   operator/ (const IVector4& vec) const;
            IVector4&  operator+=(const int value);
            IVector4&  operator+=(const int arr[4]);
            IVector4&  operator+=(const IVector4& vec);
            IVector4&  operator-=(const int value);
            IVector4&  operator-=(const int arr[4]);
            IVector4&  operator-=(const IVector4& vec);
            IVector4&  operator*=(const int value);
            IVector4&  operator*=(const int arr[4]);
            IVector4&  operator*=(const IVector4& vec);
            IVector4&  operator*=(const Matrix4x4& mat);
            IVector4&  operator/=(const int value);
            IVector4&  operator/=(const int arr[4]);
            IVector4&  operator/=(const IVector4& vec);
            bool       operator==(const int value);
            bool       operator==(const int arr[4]);
            bool       operator==(const IVector4& vec);
            int&       operator[](const size_t index);
            const int& operator[](const size_t index) const;

            int&       X();
            const int& X() const;
            int&       Y();
            const int& Y() const;
            int&       Z();
            const int& Z() const;
            int&       W();
            const int& W() const;

            int     Dot      (const IVector4& vec) const;
            float   Length   () const;
            Vector4 Normalize() const;
            float   Distance (const IVector4& vec) const;

            int data[4]{ { 0 } };
    };

    class UIVector2
    {
        public:
            UIVector2() { }
            UIVector2(const uint value);
            UIVector2(const uint arr[2]);
            UIVector2(const uint x, const uint y);
            UIVector2(const UIVector2& vec);

            operator Vector2 () const;
            operator IVector2() const;

            UIVector2&  operator= (const uint value);
            UIVector2&  operator= (const uint arr[2]);
            UIVector2&  operator= (const UIVector2& vec);
            UIVector2   operator+ (const uint value) const;
            UIVector2   operator+ (const uint arr[2]) const;
            UIVector2   operator+ (const UIVector2& vec) const;
            UIVector2   operator- (const uint value) const;
            UIVector2   operator- (const uint arr[2]) const;
            UIVector2   operator- (const UIVector2& vec) const;
            UIVector2   operator* (const uint value) const;
            UIVector2   operator* (const uint arr[2]) const;
            UIVector2   operator* (const UIVector2& vec) const;
            UIVector2   operator/ (const uint value) const;
            UIVector2   operator/ (const uint arr[2]) const;
            UIVector2   operator/ (const UIVector2& vec) const;
            UIVector2&  operator+=(const uint value);
            UIVector2&  operator+=(const uint arr[2]);
            UIVector2&  operator+=(const UIVector2& vec);
            UIVector2&  operator-=(const uint value);
            UIVector2&  operator-=(const uint arr[2]);
            UIVector2&  operator-=(const UIVector2& vec);
            UIVector2&  operator*=(const uint value);
            UIVector2&  operator*=(const uint arr[2]);
            UIVector2&  operator*=(const UIVector2& vec);
            UIVector2&  operator/=(const uint value);
            UIVector2&  operator/=(const uint arr[2]);
            UIVector2&  operator/=(const UIVector2& vec);
            bool        operator==(const uint value);
            bool        operator==(const uint arr[2]);
            bool        operator==(const UIVector2& vec);
            uint&       operator[](const size_t index);
            const uint& operator[](const size_t index) const;

            uint&       X();
            const uint& X() const;
            uint&       Y();
            const uint& Y() const;
            
            uint    Dot      (const UIVector2& vec) const;
            float   Length   () const;
            Vector2 Normalize() const;
            float   Distance (const UIVector2& vec) const;

            uint data[2]{ { 0 } };
    };

    class UIVector3
    {
        public:
            UIVector3() { }
            UIVector3(const uint value);
            UIVector3(const uint arr[3]);
            UIVector3(const uint x, const uint y, const uint z);
            UIVector3(const UIVector2& vec, const uint z);
            UIVector3(const UIVector3& vec);

            operator Vector3 () const;
            operator IVector3() const;

            UIVector3&  operator= (const uint value);
            UIVector3&  operator= (const uint arr[3]);
            UIVector3&  operator= (const UIVector3& vec);
            UIVector3   operator+ (const uint value) const;
            UIVector3   operator+ (const uint arr[3]) const;
            UIVector3   operator+ (const UIVector3& vec) const;
            UIVector3   operator- (const uint value) const;
            UIVector3   operator- (const uint arr[3]) const;
            UIVector3   operator- (const UIVector3& vec) const;
            UIVector3   operator* (const uint value) const;
            UIVector3   operator* (const uint arr[3]) const;
            UIVector3   operator* (const UIVector3& vec) const;
            UIVector3   operator/ (const uint value) const;
            UIVector3   operator/ (const uint arr[3]) const;
            UIVector3   operator/ (const UIVector3& vec) const;
            UIVector3&  operator+=(const uint value);
            UIVector3&  operator+=(const uint arr[3]);
            UIVector3&  operator+=(const UIVector3& vec);
            UIVector3&  operator-=(const uint value);
            UIVector3&  operator-=(const uint arr[3]);
            UIVector3&  operator-=(const UIVector3& vec);
            UIVector3&  operator*=(const uint value);
            UIVector3&  operator*=(const uint arr[3]);
            UIVector3&  operator*=(const UIVector3& vec);
            UIVector3&  operator/=(const uint value);
            UIVector3&  operator/=(const uint arr[3]);
            UIVector3&  operator/=(const UIVector3& vec);
            bool        operator==(const uint value);
            bool        operator==(const uint arr[3]);
            bool        operator==(const UIVector3& vec);
            uint&       operator[](const size_t index);
            const uint& operator[](const size_t index) const;

            uint&       X();
            const uint& X() const;
            uint&       Y();
            const uint& Y() const;
            uint&       Z();
            const uint& Z() const;
            
            uint      Dot      (const UIVector3& vec) const;
            UIVector3 Cross    (const UIVector3& vec) const;
            float     Length   () const;
            Vector3   Normalize() const;
            float     Distance (const UIVector3& vec) const;

            uint data[3]{ { 0 } };
    };

    class UIVector4
    {
        public:
            UIVector4() { }
            UIVector4(const uint value);
            UIVector4(const uint arr[4]);
            UIVector4(const uint x, const uint y, const uint z, const uint w);
            UIVector4(const UIVector2& vec, const uint z, const uint w);
            UIVector4(const UIVector3& vec, const uint w);
            UIVector4(const UIVector4& vec);

            operator Vector4 () const;
            operator IVector4() const;

            UIVector4&  operator= (const uint value);
            UIVector4&  operator= (const uint arr[4]);
            UIVector4&  operator= (const UIVector4& vec);
            UIVector4   operator+ (const uint value) const;
            UIVector4   operator+ (const uint arr[4]) const;
            UIVector4   operator+ (const UIVector4& vec) const;
            UIVector4   operator- (const uint value) const;
            UIVector4   operator- (const uint arr[4]) const;
            UIVector4   operator- (const UIVector4& vec) const;
            UIVector4   operator* (const uint value) const;
            UIVector4   operator* (const uint arr[4]) const;
            UIVector4   operator* (const UIVector4& vec) const;
            UIVector4   operator* (const Matrix4x4& mat) const;
            UIVector4   operator/ (const uint value) const;
            UIVector4   operator/ (const uint arr[4]) const;
            UIVector4   operator/ (const UIVector4& vec) const;
            UIVector4&  operator+=(const uint value);
            UIVector4&  operator+=(const uint arr[4]);
            UIVector4&  operator+=(const UIVector4& vec);
            UIVector4&  operator-=(const uint value);
            UIVector4&  operator-=(const uint arr[4]);
            UIVector4&  operator-=(const UIVector4& vec);
            UIVector4&  operator*=(const uint value);
            UIVector4&  operator*=(const uint arr[4]);
            UIVector4&  operator*=(const UIVector4& vec);
            UIVector4&  operator*=(const Matrix4x4& mat);
            UIVector4&  operator/=(const uint value);
            UIVector4&  operator/=(const uint arr[4]);
            UIVector4&  operator/=(const UIVector4& vec);
            bool        operator==(const uint value);
            bool        operator==(const uint arr[4]);
            bool        operator==(const UIVector4& vec);
            uint&       operator[](const size_t index);
            const uint& operator[](const size_t index) const;

            uint&       X();
            const uint& X() const;
            uint&       Y();
            const uint& Y() const;
            uint&       Z();
            const uint& Z() const;
            uint&       W();
            const uint& W() const;

            uint    Dot      (const UIVector4& vec) const;
            float   Length   () const;
            Vector4 Normalize() const;
            float   Distance (const UIVector4& vec) const;

            uint data[4]{ { 0 } };
    };
}

#endif // VIOLET_ENGINE_VECTOR_HPP