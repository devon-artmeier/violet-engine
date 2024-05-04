#ifndef VIOLET_ENGINE_VECTOR_HPP
#define VIOLET_ENGINE_VECTOR_HPP

namespace Violet
{
    class Vector2D
    {
        public:
            Vector2D() { }
            Vector2D(const float value);
            Vector2D(const float x, const float y);
            Vector2D(const Vector2D& vec);

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
            Vector3D(const Vector3D& vec);

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
            Vector4D(const Vector4D& vec);

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

            float    Dot      (const Vector4D& other) const;
            float    Length   () const;
            Vector4D Normalize() const;
            float    Distance (const Vector4D& other) const;

        private:
            float data[4]{ { 0 } };
    };
}

#endif // VIOLET_ENGINE_VECTOR_HPP