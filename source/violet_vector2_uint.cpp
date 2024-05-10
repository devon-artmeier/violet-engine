#include "violet_engine_internal.hpp"

namespace Violet
{
    UIVector2::UIVector2(const uint value)
    {
        this->data[0] = value;
        this->data[1] = value;
    }

    UIVector2::UIVector2(const uint arr[2])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
    }

    UIVector2::UIVector2(const uint x, const uint y)
    {
        this->data[0] = x;
        this->data[1] = y;
    }

    UIVector2::UIVector2(const UIVector2& vec)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
    }

    UIVector2::operator Vector2() const
    {
        return Vector2(this->data[0], this->data[1]);
    }

    UIVector2::operator IVector2() const
    {
        return IVector2(this->data[0], this->data[1]);
    }

    UIVector2& UIVector2::operator=(const UIVector2& vec)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        return *this;
    }

    UIVector2 UIVector2::operator+(const UIVector2& vec) const
    {
        return UIVector2(this->data[0] + vec[0],
                         this->data[1] + vec[1]);
    }

    UIVector2 UIVector2::operator-(const UIVector2& vec) const
    {
        return UIVector2(this->data[0] - vec[0],
                         this->data[1] - vec[1]);
    }

    UIVector2 UIVector2::operator*(const UIVector2& vec) const
    {
        return UIVector2(this->data[0] * vec[0],
                         this->data[1] * vec[1]);
    }

    UIVector2 UIVector2::operator/(const UIVector2& vec) const
    {
        return UIVector2(this->data[0] / vec[0],
                         this->data[1] / vec[1]);
    }

    UIVector2& UIVector2::operator+=(const UIVector2& vec)
    {
        this->data[0] += vec[0];
        this->data[1] += vec[1];
        return *this;
    }

    UIVector2& UIVector2::operator-=(const UIVector2& vec)
    {
        this->data[0] -= vec[0];
        this->data[1] -= vec[1];
        return *this;
    }

    UIVector2& UIVector2::operator*=(const UIVector2& vec)
    {
        this->data[0] *= vec[0];
        this->data[1] *= vec[1];
        return *this;
    }

    UIVector2& UIVector2::operator/=(const UIVector2& vec)
    {
        this->data[0] /= vec[0];
        this->data[1] /= vec[1];
        return *this;
    }

    bool UIVector2::operator==(const UIVector2& vec)
    {
        return this->data[0] == vec[0] &&
               this->data[1] == vec[1];
    }

    uint& UIVector2::operator[](const size_t index)
    {
        return this->data[index];
    }

    const uint& UIVector2::operator[](const size_t index) const
    {
        return this->data[index];
    }

    uint& UIVector2::X()
    {
        return this->data[0];
    }

    const uint& UIVector2::X() const
    {
        return this->data[0];
    }

    uint& UIVector2::Y()
    {
        return this->data[1];
    }

    const uint& UIVector2::Y() const
    {
        return this->data[1];
    }

    uint UIVector2::Dot(const UIVector2& vec) const
    {
        return (this->data[0] * vec[0]) +
               (this->data[1] * vec[1]);
    }

    float UIVector2::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]));
    }

    Vector2 UIVector2::Normalize() const
    {
        return Vector2(this->data[0] / this->Length(),
                       this->data[1] / this->Length());
    }

    float UIVector2::Distance(const UIVector2& vec) const
    {
        return (*this - vec).Length();
    }
}