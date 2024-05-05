#include "violet_engine_internal.hpp"

namespace Violet
{
    Vector3D::Vector3D(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
    }

    Vector3D::Vector3D(const float arr[3])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
    }

    Vector3D::Vector3D(const float x, const float y, const float z)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
    }

    Vector3D::Vector3D(const Vector2D& vec, const float z)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
        this->data[2] = z;
    }

    Vector3D::Vector3D(const Vector3D& vec)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
        this->data[2] = vec.data[2];
    }

    Vector3D& Vector3D::operator=(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
        return *this;
    }

    Vector3D& Vector3D::operator=(const float arr[3])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
        return *this;
    }

    Vector3D& Vector3D::operator=(const Vector3D& vec)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
        this->data[2] = vec.data[2];
        return *this;
    }

    Vector3D Vector3D::operator+(const float value) const
    {
        return Vector3D(this->data[0] + value,
                        this->data[1] + value,
                        this->data[2] + value);
    }

    Vector3D Vector3D::operator+(const float arr[3]) const
    {
        return Vector3D(this->data[0] + arr[0],
                        this->data[1] + arr[1],
                        this->data[2] + arr[2]);
    }

    Vector3D Vector3D::operator+(const Vector3D& vec) const
    {
        return Vector3D(this->data[0] + vec.data[0],
                        this->data[1] + vec.data[1],
                        this->data[2] + vec.data[2]);
    }

    Vector3D Vector3D::operator-(const float value) const
    {
        return Vector3D(this->data[0] - value,
                        this->data[1] - value,
                        this->data[2] - value);
    }

    Vector3D Vector3D::operator-(const float arr[3]) const
    {
        return Vector3D(this->data[0] - arr[0],
                        this->data[1] - arr[1],
                        this->data[2] - arr[2]);
    }

    Vector3D Vector3D::operator-(const Vector3D& vec) const
    {
        return Vector3D(this->data[0] - vec.data[0],
                        this->data[1] - vec.data[1],
                        this->data[2] - vec.data[2]);
    }

    Vector3D Vector3D::operator*(const float value) const
    {
        return Vector3D(this->data[0] * value,
                        this->data[1] * value,
                        this->data[2] * value);
    }

    Vector3D Vector3D::operator*(const float arr[3]) const
    {
        return Vector3D(this->data[0] * arr[0],
                        this->data[1] * arr[1],
                        this->data[2] * arr[2]);
    }

    Vector3D Vector3D::operator*(const Vector3D& vec) const
    {
        return Vector3D(this->data[0] * vec.data[0],
                        this->data[1] * vec.data[1],
                        this->data[2] * vec.data[2]);
    }

    Vector3D Vector3D::operator/(const float value) const
    {
        return Vector3D(this->data[0] / value,
                        this->data[1] / value,
                        this->data[2] / value);
    }

    Vector3D Vector3D::operator/(const float arr[3]) const
    {
        return Vector3D(this->data[0] / arr[0],
                        this->data[1] / arr[1],
                        this->data[2] / arr[2]);
    }

    Vector3D Vector3D::operator/(const Vector3D& vec) const
    {
        return Vector3D(this->data[0] / vec.data[0],
                        this->data[1] / vec.data[1],
                        this->data[2] / vec.data[2]);
    }

    Vector3D& Vector3D::operator+=(const float value)
    {
        this->data[0] += value;
        this->data[1] += value;
        this->data[2] += value;
        return *this;
    }

    Vector3D& Vector3D::operator+=(const float arr[3])
    {
        this->data[0] += arr[0];
        this->data[1] += arr[1];
        this->data[2] += arr[2];
        return *this;
    }

    Vector3D& Vector3D::operator+=(const Vector3D& vec)
    {
        this->data[0] += vec.data[0];
        this->data[1] += vec.data[1];
        this->data[2] += vec.data[2];
        return *this;
    }

    Vector3D& Vector3D::operator-=(const float value)
    {
        this->data[0] -= value;
        this->data[1] -= value;
        this->data[2] -= value;
        return *this;
    }

    Vector3D& Vector3D::operator-=(const float arr[3])
    {
        this->data[0] -= arr[0];
        this->data[1] -= arr[1];
        this->data[2] -= arr[2];
        return *this;
    }

    Vector3D& Vector3D::operator-=(const Vector3D& vec)
    {
        this->data[0] -= vec.data[0];
        this->data[1] -= vec.data[1];
        this->data[2] -= vec.data[2];
        return *this;
    }

    Vector3D& Vector3D::operator*=(const float value)
    {
        this->data[0] *= value;
        this->data[1] *= value;
        this->data[2] *= value;
        return *this;
    }

    Vector3D& Vector3D::operator*=(const float arr[3])
    {
        this->data[0] *= arr[0];
        this->data[1] *= arr[1];
        this->data[2] *= arr[2];
        return *this;
    }

    Vector3D& Vector3D::operator*=(const Vector3D& vec)
    {
        this->data[0] *= vec.data[0];
        this->data[1] *= vec.data[1];
        this->data[2] *= vec.data[2];
        return *this;
    }

    Vector3D& Vector3D::operator/=(const float value)
    {
        this->data[0] /= value;
        this->data[1] /= value;
        this->data[2] /= value;
        return *this;
    }

    Vector3D& Vector3D::operator/=(const float arr[3])
    {
        this->data[0] /= arr[0];
        this->data[1] /= arr[1];
        this->data[2] /= arr[2];
        return *this;
    }

    Vector3D& Vector3D::operator/=(const Vector3D& vec)
    {
        this->data[0] /= vec.data[0];
        this->data[1] /= vec.data[1];
        this->data[2] /= vec.data[2];
        return *this;
    }

    bool Vector3D::operator==(const float value)
    {
        return this->data[0] == value &&
               this->data[1] == value &&
               this->data[2] == value;
    }

    bool Vector3D::operator==(const float arr[3])
    {
        return this->data[0] == arr[0] &&
               this->data[1] == arr[1] &&
               this->data[2] == arr[2];
    }

    bool Vector3D::operator==(const Vector3D& vec)
    {
        return this->data[0] == vec.data[0] &&
               this->data[1] == vec.data[1] &&
               this->data[2] == vec.data[2];
    }

    float& Vector3D::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float& Vector3D::operator[](const size_t index) const
    {
        return this->data[index];
    }

    float& Vector3D::X()
    {
        return this->data[0];
    }

    const float& Vector3D::X() const
    {
        return this->data[0];
    }

    float& Vector3D::Y()
    {
        return this->data[1];
    }

    const float& Vector3D::Y() const
    {
        return this->data[1];
    }

    float& Vector3D::Z()
    {
        return this->data[2];
    }

    const float& Vector3D::Z() const
    {
        return this->data[2];
    }

    float Vector3D::Dot(const Vector3D& vec) const
    {
        return (this->data[0] * vec.data[0]) +
               (this->data[1] * vec.data[1]) +
               (this->data[2] * vec.data[2]);
    }

    Vector3D Vector3D::Cross(const Vector3D& vec) const
    {
        return Vector3D((this->data[1] * vec.data[2]) - (vec.data[1] * this->data[2]),
                        (this->data[2] * vec.data[0]) - (vec.data[2] * this->data[0]),
                        (this->data[0] * vec.data[1]) - (vec.data[0] * this->data[1]));
    }

    float Vector3D::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]) +
                    (this->data[2] * this->data[2]));
    }

    Vector3D Vector3D::Normalize() const
    {
        return Vector3D(this->data[0] / this->Length(),
                        this->data[1] / this->Length(),
                        this->data[2] / this->Length());
    }

    float Vector3D::Distance(const Vector3D& vec) const
    {
        return (*this - vec).Length();
    }
}