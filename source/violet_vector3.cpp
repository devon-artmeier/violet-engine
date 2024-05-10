#include "violet_engine_internal.hpp"

namespace Violet
{
    Vector3::Vector3(const int value)
    {
        this->data[0] = static_cast<float>(value);
        this->data[1] = static_cast<float>(value);
        this->data[2] = static_cast<float>(value);
    }

    Vector3::Vector3(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
    }

    Vector3::Vector3(const float arr[3])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
    }

    Vector3::Vector3(const float x, const float y, const float z)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
    }

    Vector3::Vector3(const Vector2& vec, const float z)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = z;
    }

    Vector3::Vector3(const Vector3& vec)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = vec[2];
    }

    Vector3::operator IVector3() const
    {
        return IVector3(this->data[0], this->data[1], this->data[2]);
    }

    Vector3::operator UIVector3() const
    {
        return UIVector3(this->data[0], this->data[1], this->data[2]);
    }

    Vector3 Vector3::operator+(const Vector3& vec) const
    {
        return Vector3(this->data[0] + vec[0],
                       this->data[1] + vec[1],
                       this->data[2] + vec[2]);
    }

    Vector3 Vector3::operator-(const Vector3& vec) const
    {
        return Vector3(this->data[0] - vec[0],
                       this->data[1] - vec[1],
                       this->data[2] - vec[2]);
    }

    Vector3 Vector3::operator*(const Vector3& vec) const
    {
        return Vector3(this->data[0] * vec[0],
                       this->data[1] * vec[1],
                       this->data[2] * vec[2]);
    }

    Vector3 Vector3::operator/(const Vector3& vec) const
    {
        return Vector3(this->data[0] / vec[0],
                       this->data[1] / vec[1],
                       this->data[2] / vec[2]);
    }

    Vector3& Vector3::operator+=(const Vector3& vec)
    {
        this->data[0] += vec[0];
        this->data[1] += vec[1];
        this->data[2] += vec[2];
        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3& vec)
    {
        this->data[0] -= vec[0];
        this->data[1] -= vec[1];
        this->data[2] -= vec[2];
        return *this;
    }

    Vector3& Vector3::operator*=(const Vector3& vec)
    {
        this->data[0] *= vec[0];
        this->data[1] *= vec[1];
        this->data[2] *= vec[2];
        return *this;
    }

    Vector3& Vector3::operator/=(const Vector3& vec)
    {
        this->data[0] /= vec[0];
        this->data[1] /= vec[1];
        this->data[2] /= vec[2];
        return *this;
    }

    bool Vector3::operator==(const Vector3& vec)
    {
        return this->data[0] == vec[0] &&
               this->data[1] == vec[1] &&
               this->data[2] == vec[2];
    }

    float& Vector3::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float& Vector3::operator[](const size_t index) const
    {
        return this->data[index];
    }

    float& Vector3::X()
    {
        return this->data[0];
    }

    const float& Vector3::X() const
    {
        return this->data[0];
    }

    float& Vector3::Y()
    {
        return this->data[1];
    }

    const float& Vector3::Y() const
    {
        return this->data[1];
    }

    float& Vector3::Z()
    {
        return this->data[2];
    }

    const float& Vector3::Z() const
    {
        return this->data[2];
    }

    float Vector3::Dot(const Vector3& vec) const
    {
        return (this->data[0] * vec[0]) +
               (this->data[1] * vec[1]) +
               (this->data[2] * vec[2]);
    }

    Vector3 Vector3::Cross(const Vector3& vec) const
    {
        return Vector3((this->data[1] * vec[2]) - (vec[1] * this->data[2]),
                       (this->data[2] * vec[0]) - (vec[2] * this->data[0]),
                       (this->data[0] * vec[1]) - (vec[0] * this->data[1]));
    }

    float Vector3::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]) +
                    (this->data[2] * this->data[2]));
    }

    Vector3 Vector3::Normalize() const
    {
        return Vector3(this->data[0] / this->Length(),
                       this->data[1] / this->Length(),
                       this->data[2] / this->Length());
    }

    float Vector3::Distance(const Vector3& vec) const
    {
        return (*this - vec).Length();
    }
}