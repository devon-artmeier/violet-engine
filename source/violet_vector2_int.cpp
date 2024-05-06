#include "violet_engine_internal.hpp"

namespace Violet
{
    IVector2::IVector2(const int value)
    {
        this->data[0] = value;
        this->data[1] = value;
    }

    IVector2::IVector2(const int arr[2])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
    }

    IVector2::IVector2(const int x, const int y)
    {
        this->data[0] = x;
        this->data[1] = y;
    }

    IVector2::IVector2(const IVector2& vec)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
    }

    IVector2::operator Vector2() const
    {
        return Vector2(this->data[0], this->data[1]);
    }

    IVector2::operator UIVector2() const
    {
        return UIVector2(this->data[0], this->data[1]);
    }

    IVector2& IVector2::operator=(const int value)
    {
        this->data[0] = value;
        this->data[1] = value;
        return *this;
    }

    IVector2& IVector2::operator=(const int arr[2])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        return *this;
    }

    IVector2& IVector2::operator=(const IVector2& vec)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
        return *this;
    }

    IVector2 IVector2::operator+(const int value) const
    {
        return IVector2(this->data[0] + value,
                        this->data[1] + value);
    }

    IVector2 IVector2::operator+(const int arr[2]) const
    {
        return IVector2(this->data[0] + arr[0],
                        this->data[1] + arr[1]);
    }

    IVector2 IVector2::operator+(const IVector2& vec) const
    {
        return IVector2(this->data[0] + vec.data[0],
                        this->data[1] + vec.data[1]);
    }

    IVector2 IVector2::operator-(const int value) const
    {
        return IVector2(this->data[0] - value,
                        this->data[1] - value);
    }

    IVector2 IVector2::operator-(const int arr[2]) const
    {
        return IVector2(this->data[0] - arr[0],
                        this->data[1] - arr[1]);
    }

    IVector2 IVector2::operator-(const IVector2& vec) const
    {
        return IVector2(this->data[0] - vec.data[0],
                        this->data[1] - vec.data[1]);
    }

    IVector2 IVector2::operator*(const int value) const
    {
        return IVector2(this->data[0] * value,
                        this->data[1] * value);
    }

    IVector2 IVector2::operator*(const int arr[2]) const
    {
        return IVector2(this->data[0] * arr[0],
                        this->data[1] * arr[1]);
    }

    IVector2 IVector2::operator*(const IVector2& vec) const
    {
        return IVector2(this->data[0] * vec.data[0],
                        this->data[1] * vec.data[1]);
    }

    IVector2 IVector2::operator/(const int value) const
    {
        return IVector2(this->data[0] / value,
                        this->data[1] / value);
    }

    IVector2 IVector2::operator/(const int arr[2]) const
    {
        return IVector2(this->data[0] / arr[0],
                        this->data[1] / arr[1]);
    }

    IVector2 IVector2::operator/(const IVector2& vec) const
    {
        return IVector2(this->data[0] / vec.data[0],
                        this->data[1] / vec.data[1]);
    }

    IVector2& IVector2::operator+=(const int value)
    {
        this->data[0] += value;
        this->data[1] += value;
        return *this;
    }

    IVector2& IVector2::operator+=(const int arr[2])
    {
        this->data[0] += arr[0];
        this->data[1] += arr[1];
        return *this;
    }

    IVector2& IVector2::operator+=(const IVector2& vec)
    {
        this->data[0] += vec.data[0];
        this->data[1] += vec.data[1];
        return *this;
    }

    IVector2& IVector2::operator-=(const int value)
    {
        this->data[0] -= value;
        this->data[1] -= value;
        return *this;
    }

    IVector2& IVector2::operator-=(const int arr[2])
    {
        this->data[0] -= arr[0];
        this->data[1] -= arr[1];
        return *this;
    }

    IVector2& IVector2::operator-=(const IVector2& vec)
    {
        this->data[0] -= vec.data[0];
        this->data[1] -= vec.data[1];
        return *this;
    }

    IVector2& IVector2::operator*=(const int value)
    {
        this->data[0] *= value;
        this->data[1] *= value;
        return *this;
    }

    IVector2& IVector2::operator*=(const int arr[2])
    {
        this->data[0] *= arr[0];
        this->data[1] *= arr[1];
        return *this;
    }

    IVector2& IVector2::operator*=(const IVector2& vec)
    {
        this->data[0] *= vec.data[0];
        this->data[1] *= vec.data[1];
        return *this;
    }

    IVector2& IVector2::operator/=(const int value)
    {
        this->data[0] /= value;
        this->data[1] /= value;
        return *this;
    }

    IVector2& IVector2::operator/=(const int arr[2])
    {
        this->data[0] /= arr[0];
        this->data[1] /= arr[1];
        return *this;
    }

    IVector2& IVector2::operator/=(const IVector2& vec)
    {
        this->data[0] /= vec.data[0];
        this->data[1] /= vec.data[1];
        return *this;
    }

    bool IVector2::operator==(const int value)
    {
        return this->data[0] == value &&
               this->data[1] == value;
    }

    bool IVector2::operator==(const int arr[2])
    {
        return this->data[0] == arr[0] &&
               this->data[1] == arr[1];
    }

    bool IVector2::operator==(const IVector2& vec)
    {
        return this->data[0] == vec.data[0] &&
               this->data[1] == vec.data[1];
    }

    int& IVector2::operator[](const size_t index)
    {
        return this->data[index];
    }

    const int& IVector2::operator[](const size_t index) const
    {
        return this->data[index];
    }

    int& IVector2::X()
    {
        return this->data[0];
    }

    const int& IVector2::X() const
    {
        return this->data[0];
    }

    int& IVector2::Y()
    {
        return this->data[1];
    }

    const int& IVector2::Y() const
    {
        return this->data[1];
    }

    int IVector2::Dot(const IVector2& vec) const
    {
        return (this->data[0] * vec.data[0]) +
               (this->data[1] * vec.data[1]);
    }

    float IVector2::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]));
    }

    Vector2 IVector2::Normalize() const
    {
        return Vector2(this->data[0] / this->Length(),
                       this->data[1] / this->Length());
    }

    float IVector2::Distance(const IVector2& vec) const
    {
        return (*this - vec).Length();
    }
}