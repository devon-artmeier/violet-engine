#include "violet_engine_internal.hpp"

namespace Violet
{
    Vector2D::Vector2D(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
    }

    Vector2D::Vector2D(const float arr[2])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
    }

    Vector2D::Vector2D(const float x, const float y)
    {
        this->data[0] = x;
        this->data[1] = y;
    }

    Vector2D::Vector2D(const Vector2D& vec)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
    }

    Vector2D& Vector2D::operator=(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
        return *this;
    }

    Vector2D& Vector2D::operator=(const float arr[2])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        return *this;
    }

    Vector2D& Vector2D::operator=(const Vector2D& vec)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
        return *this;
    }

    Vector2D Vector2D::operator+(const float value) const
    {
        return Vector2D(this->data[0] + value,
                        this->data[1] + value);
    }

    Vector2D Vector2D::operator+(const float arr[2]) const
    {
        return Vector2D(this->data[0] + arr[0],
                        this->data[1] + arr[1]);
    }

    Vector2D Vector2D::operator+(const Vector2D& vec) const
    {
        return Vector2D(this->data[0] + vec.data[0],
                        this->data[1] + vec.data[1]);
    }

    Vector2D Vector2D::operator-(const float value) const
    {
        return Vector2D(this->data[0] - value,
                        this->data[1] - value);
    }

    Vector2D Vector2D::operator-(const float arr[2]) const
    {
        return Vector2D(this->data[0] - arr[0],
                        this->data[1] - arr[1]);
    }

    Vector2D Vector2D::operator-(const Vector2D& vec) const
    {
        return Vector2D(this->data[0] - vec.data[0],
                        this->data[1] - vec.data[1]);
    }

    Vector2D Vector2D::operator*(const float value) const
    {
        return Vector2D(this->data[0] * value,
                        this->data[1] * value);
    }

    Vector2D Vector2D::operator*(const float arr[2]) const
    {
        return Vector2D(this->data[0] * arr[0],
                        this->data[1] * arr[1]);
    }

    Vector2D Vector2D::operator*(const Vector2D& vec) const
    {
        return Vector2D(this->data[0] * vec.data[0],
                        this->data[1] * vec.data[1]);
    }

    Vector2D Vector2D::operator/(const float value) const
    {
        return Vector2D(this->data[0] / value,
                        this->data[1] / value);
    }

    Vector2D Vector2D::operator/(const float arr[2]) const
    {
        return Vector2D(this->data[0] / arr[0],
                        this->data[1] / arr[1]);
    }

    Vector2D Vector2D::operator/(const Vector2D& vec) const
    {
        return Vector2D(this->data[0] / vec.data[0],
                        this->data[1] / vec.data[1]);
    }

    Vector2D& Vector2D::operator+=(const float value)
    {
        this->data[0] += value;
        this->data[1] += value;
        return *this;
    }

    Vector2D& Vector2D::operator+=(const float arr[2])
    {
        this->data[0] += arr[0];
        this->data[1] += arr[1];
        return *this;
    }

    Vector2D& Vector2D::operator+=(const Vector2D& vec)
    {
        this->data[0] += vec.data[0];
        this->data[1] += vec.data[1];
        return *this;
    }

    Vector2D& Vector2D::operator-=(const float value)
    {
        this->data[0] -= value;
        this->data[1] -= value;
        return *this;
    }

    Vector2D& Vector2D::operator-=(const float arr[2])
    {
        this->data[0] -= arr[0];
        this->data[1] -= arr[1];
        return *this;
    }

    Vector2D& Vector2D::operator-=(const Vector2D& vec)
    {
        this->data[0] -= vec.data[0];
        this->data[1] -= vec.data[1];
        return *this;
    }

    Vector2D& Vector2D::operator*=(const float value)
    {
        this->data[0] *= value;
        this->data[1] *= value;
        return *this;
    }

    Vector2D& Vector2D::operator*=(const float arr[2])
    {
        this->data[0] *= arr[0];
        this->data[1] *= arr[1];
        return *this;
    }

    Vector2D& Vector2D::operator*=(const Vector2D& vec)
    {
        this->data[0] *= vec.data[0];
        this->data[1] *= vec.data[1];
        return *this;
    }

    Vector2D& Vector2D::operator/=(const float value)
    {
        this->data[0] /= value;
        this->data[1] /= value;
        return *this;
    }

    Vector2D& Vector2D::operator/=(const float arr[2])
    {
        this->data[0] /= arr[0];
        this->data[1] /= arr[1];
        return *this;
    }

    Vector2D& Vector2D::operator/=(const Vector2D& vec)
    {
        this->data[0] /= vec.data[0];
        this->data[1] /= vec.data[1];
        return *this;
    }

    bool Vector2D::operator==(const float value)
    {
        return this->data[0] == value &&
               this->data[1] == value;
    }

    bool Vector2D::operator==(const float arr[2])
    {
        return this->data[0] == arr[0] &&
               this->data[1] == arr[1];
    }

    bool Vector2D::operator==(const Vector2D& vec)
    {
        return this->data[0] == vec.data[0] &&
               this->data[1] == vec.data[1];
    }

    float& Vector2D::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float& Vector2D::operator[](const size_t index) const
    {
        return this->data[index];
    }

    float& Vector2D::X()
    {
        return this->data[0];
    }

    const float& Vector2D::X() const
    {
        return this->data[0];
    }

    float& Vector2D::Y()
    {
        return this->data[1];
    }

    const float& Vector2D::Y() const
    {
        return this->data[1];
    }

    float Vector2D::Dot(const Vector2D& vec) const
    {
        return (this->data[0] * vec.data[0]) +
               (this->data[1] * vec.data[1]);
    }

    float Vector2D::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]));
    }

    Vector2D Vector2D::Normalize() const
    {
        return Vector2D(this->data[0] / this->Length(),
                        this->data[1] / this->Length());
    }

    float Vector2D::Distance(const Vector2D& vec) const
    {
        return (*this - vec).Length();
    }
}