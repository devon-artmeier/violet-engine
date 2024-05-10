#include "violet_engine_internal.hpp"

namespace Violet
{
    Vector4::Vector4(const int value)
    {
        this->data[0] = static_cast<float>(value);
        this->data[1] = static_cast<float>(value);
        this->data[2] = static_cast<float>(value);
        this->data[3] = static_cast<float>(value);
    }

    Vector4::Vector4(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
        this->data[3] = value;
    }

    Vector4::Vector4(const float arr[4])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
        this->data[3] = arr[3];
    }

    Vector4::Vector4(const float x, const float y, const float z, const float w)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
        this->data[3] = w;
    }

    Vector4::Vector4(const Vector2& vec, const float z, const float w)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = z;
        this->data[3] = w;
    }

    Vector4::Vector4(const Vector3& vec, const float w)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = vec[2];
        this->data[3] = w;
    }

    Vector4::Vector4(const Vector4& vec)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = vec[2];
        this->data[3] = vec[3];
    }

    Vector4::operator IVector4() const
    {
        return IVector4(this->data[0], this->data[1], this->data[2], this->data[3]);
    }

    Vector4::operator UIVector4() const
    {
        return UIVector4(this->data[0], this->data[1], this->data[2], this->data[3]);
    }

    Vector4 Vector4::operator+(const Vector4& vec) const
    {
        return Vector4(this->data[0] + vec[0],
                       this->data[1] + vec[1],
                       this->data[2] + vec[2],
                       this->data[3] + vec[3]);
    }

    Vector4 Vector4::operator-(const Vector4& vec) const
    {
        return Vector4(this->data[0] - vec[0],
                       this->data[1] - vec[1],
                       this->data[2] - vec[2],
                       this->data[3] - vec[3]);
    }

    Vector4 Vector4::operator*(const Vector4& vec) const
    {
        return Vector4(this->data[0] * vec[0],
                       this->data[1] * vec[1],
                       this->data[2] * vec[2],
                       this->data[3] * vec[3]);
    }

    Vector4 Vector4::operator/(const Vector4& vec) const
    {
        return Vector4(this->data[0] / vec[0],
                       this->data[1] / vec[1],
                       this->data[2] / vec[2],
                       this->data[3] / vec[3]);
    }

    Vector4& Vector4::operator+=(const Vector4& vec)
    {
        this->data[0] += vec[0];
        this->data[1] += vec[1];
        this->data[2] += vec[2];
        this->data[3] += vec[3];
        return *this;
    }

    Vector4& Vector4::operator-=(const Vector4& vec)
    {
        this->data[0] -= vec[0];
        this->data[1] -= vec[1];
        this->data[2] -= vec[2];
        this->data[3] -= vec[3];
        return *this;
    }

    Vector4& Vector4::operator*=(const Vector4& vec)
    {
        this->data[0] *= vec[0];
        this->data[1] *= vec[1];
        this->data[2] *= vec[2];
        this->data[3] *= vec[3];
        return *this;
    }

    Vector4& Vector4::operator/=(const Vector4& vec)
    {
        this->data[0] /= vec[0];
        this->data[1] /= vec[1];
        this->data[2] /= vec[2];
        this->data[3] /= vec[3];
        return *this;
    }

    bool Vector4::operator==(const Vector4& vec)
    {
        return this->data[0] == vec[0] &&
               this->data[1] == vec[1] &&
               this->data[2] == vec[2] &&
               this->data[3] == vec[3];
    }

    float& Vector4::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float& Vector4::operator[](const size_t index) const
    {
        return this->data[index];
    }

    float& Vector4::X()
    {
        return this->data[0];
    }

    const float& Vector4::X() const
    {
        return this->data[0];
    }

    float& Vector4::Y()
    {
        return this->data[1];
    }

    const float& Vector4::Y() const
    {
        return this->data[1];
    }

    float& Vector4::Z()
    {
        return this->data[2];
    }

    const float& Vector4::Z() const
    {
        return this->data[2];
    }

    float& Vector4::W()
    {
        return this->data[3];
    }

    const float& Vector4::W() const
    {
        return this->data[3];
    }

    float Vector4::Dot(const Vector4& vec) const
    {
        return (this->data[0] * vec[0]) +
               (this->data[1] * vec[1]) +
               (this->data[2] * vec[2]) +
               (this->data[3] * vec[3]);
    }

    float Vector4::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]) +
                    (this->data[2] * this->data[2]) +
                    (this->data[3] * this->data[3]));
    }

    Vector4 Vector4::Normalize() const
    {
        return Vector4(this->data[0] / this->Length(),
                       this->data[1] / this->Length(),
                       this->data[2] / this->Length(),
                       this->data[3] / this->Length());
    }

    float Vector4::Distance(const Vector4& vec) const
    {
        return (*this - vec).Length();
    }
}