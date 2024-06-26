#include "violet_engine_internal.hpp"

namespace Violet
{
    Vector2::Vector2(const int value)
    {
        this->data[0] = static_cast<float>(value);
        this->data[1] = static_cast<float>(value);
    }

    Vector2::Vector2(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
    }

    Vector2::Vector2(const float arr[2])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
    }

    Vector2::Vector2(const float x, const float y)
    {
        this->data[0] = x;
        this->data[1] = y;
    }

    Vector2::Vector2(const Vector2& vec)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
    }

    Vector2::operator IVector2() const
    {
        return IVector2(this->data[0], this->data[1]);
    }

    Vector2::operator UIVector2() const
    {
        return UIVector2(this->data[0], this->data[1]);
    }

    Vector2 Vector2::operator+(const Vector2& vec) const
    {
        return Vector2(this->data[0] + vec[0],
                       this->data[1] + vec[1]);
    }

    Vector2 Vector2::operator-(const Vector2& vec) const
    {
        return Vector2(this->data[0] - vec[0],
                       this->data[1] - vec[1]);
    }

    Vector2 Vector2::operator*(const Vector2& vec) const
    {
        return Vector2(this->data[0] * vec[0],
                       this->data[1] * vec[1]);
    }

    Vector2 Vector2::operator/(const Vector2& vec) const
    {
        return Vector2(this->data[0] / vec[0],
                       this->data[1] / vec[1]);
    }

    Vector2& Vector2::operator+=(const Vector2& vec)
    {
        this->data[0] += vec[0];
        this->data[1] += vec[1];
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& vec)
    {
        this->data[0] -= vec[0];
        this->data[1] -= vec[1];
        return *this;
    }

    Vector2& Vector2::operator*=(const Vector2& vec)
    {
        this->data[0] *= vec[0];
        this->data[1] *= vec[1];
        return *this;
    }

    Vector2& Vector2::operator/=(const Vector2& vec)
    {
        this->data[0] /= vec[0];
        this->data[1] /= vec[1];
        return *this;
    }

    bool Vector2::operator==(const Vector2& vec)
    {
        return this->data[0] == vec[0] &&
               this->data[1] == vec[1];
    }

    float& Vector2::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float& Vector2::operator[](const size_t index) const
    {
        return this->data[index];
    }

    float& Vector2::X()
    {
        return this->data[0];
    }

    const float& Vector2::X() const
    {
        return this->data[0];
    }

    float& Vector2::Y()
    {
        return this->data[1];
    }

    const float& Vector2::Y() const
    {
        return this->data[1];
    }

    float& Vector2::R()
    {
        return this->data[0];
    }

    const float& Vector2::R() const
    {
        return this->data[0];
    }

    float& Vector2::G()
    {
        return this->data[1];
    }

    const float& Vector2::G() const
    {
        return this->data[1];
    }

    float& Vector2::S()
    {
        return this->data[0];
    }

    const float& Vector2::S() const
    {
        return this->data[0];
    }

    float& Vector2::T()
    {
        return this->data[1];
    }

    const float& Vector2::T() const
    {
        return this->data[1];
    }

    float Vector2::Dot(const Vector2& vec) const
    {
        return (this->data[0] * vec[0]) +
               (this->data[1] * vec[1]);
    }

    float Vector2::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]));
    }

    Vector2 Vector2::Normalize() const
    {
        return Vector2(this->data[0] / this->Length(),
                       this->data[1] / this->Length());
    }

    float Vector2::Distance(const Vector2& vec) const
    {
        return (*this - vec).Length();
    }
}