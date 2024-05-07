#include "violet_engine_internal.hpp"

namespace Violet
{
    IVector3::IVector3(const int value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
    }

    IVector3::IVector3(const int arr[3])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
    }

    IVector3::IVector3(const int x, const int y, const int z)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
    }

    IVector3::IVector3(const IVector2& vec, const int z)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = z;
    }

    IVector3::IVector3(const IVector3& vec)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = vec[2];
    }

    IVector3::operator Vector3() const
    {
        return Vector3(this->data[0], this->data[1], this->data[2]);
    }

    IVector3::operator UIVector3() const
    {
        return UIVector3(this->data[0], this->data[1], this->data[2]);
    }

    IVector3& IVector3::operator=(const int value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
        return *this;
    }

    IVector3& IVector3::operator=(const int arr[3])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
        return *this;
    }

    IVector3& IVector3::operator=(const IVector3& vec)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = vec[2];
        return *this;
    }

    IVector3 IVector3::operator+(const int value) const
    {
        return IVector3(this->data[0] + value,
                        this->data[1] + value,
                        this->data[2] + value);
    }

    IVector3 IVector3::operator+(const int arr[3]) const
    {
        return IVector3(this->data[0] + arr[0],
                        this->data[1] + arr[1],
                        this->data[2] + arr[2]);
    }

    IVector3 IVector3::operator+(const IVector3& vec) const
    {
        return IVector3(this->data[0] + vec[0],
                        this->data[1] + vec[1],
                        this->data[2] + vec[2]);
    }

    IVector3 IVector3::operator-(const int value) const
    {
        return IVector3(this->data[0] - value,
                        this->data[1] - value,
                        this->data[2] - value);
    }

    IVector3 IVector3::operator-(const int arr[3]) const
    {
        return IVector3(this->data[0] - arr[0],
                        this->data[1] - arr[1],
                        this->data[2] - arr[2]);
    }

    IVector3 IVector3::operator-(const IVector3& vec) const
    {
        return IVector3(this->data[0] - vec[0],
                        this->data[1] - vec[1],
                        this->data[2] - vec[2]);
    }

    IVector3 IVector3::operator*(const int value) const
    {
        return IVector3(this->data[0] * value,
                        this->data[1] * value,
                        this->data[2] * value);
    }

    IVector3 IVector3::operator*(const int arr[3]) const
    {
        return IVector3(this->data[0] * arr[0],
                        this->data[1] * arr[1],
                        this->data[2] * arr[2]);
    }

    IVector3 IVector3::operator*(const IVector3& vec) const
    {
        return IVector3(this->data[0] * vec[0],
                        this->data[1] * vec[1],
                        this->data[2] * vec[2]);
    }

    IVector3 IVector3::operator/(const int value) const
    {
        return IVector3(this->data[0] / value,
                        this->data[1] / value,
                        this->data[2] / value);
    }

    IVector3 IVector3::operator/(const int arr[3]) const
    {
        return IVector3(this->data[0] / arr[0],
                        this->data[1] / arr[1],
                        this->data[2] / arr[2]);
    }

    IVector3 IVector3::operator/(const IVector3& vec) const
    {
        return IVector3(this->data[0] / vec[0],
                        this->data[1] / vec[1],
                        this->data[2] / vec[2]);
    }

    IVector3& IVector3::operator+=(const int value)
    {
        this->data[0] += value;
        this->data[1] += value;
        this->data[2] += value;
        return *this;
    }

    IVector3& IVector3::operator+=(const int arr[3])
    {
        this->data[0] += arr[0];
        this->data[1] += arr[1];
        this->data[2] += arr[2];
        return *this;
    }

    IVector3& IVector3::operator+=(const IVector3& vec)
    {
        this->data[0] += vec[0];
        this->data[1] += vec[1];
        this->data[2] += vec[2];
        return *this;
    }

    IVector3& IVector3::operator-=(const int value)
    {
        this->data[0] -= value;
        this->data[1] -= value;
        this->data[2] -= value;
        return *this;
    }

    IVector3& IVector3::operator-=(const int arr[3])
    {
        this->data[0] -= arr[0];
        this->data[1] -= arr[1];
        this->data[2] -= arr[2];
        return *this;
    }

    IVector3& IVector3::operator-=(const IVector3& vec)
    {
        this->data[0] -= vec[0];
        this->data[1] -= vec[1];
        this->data[2] -= vec[2];
        return *this;
    }

    IVector3& IVector3::operator*=(const int value)
    {
        this->data[0] *= value;
        this->data[1] *= value;
        this->data[2] *= value;
        return *this;
    }

    IVector3& IVector3::operator*=(const int arr[3])
    {
        this->data[0] *= arr[0];
        this->data[1] *= arr[1];
        this->data[2] *= arr[2];
        return *this;
    }

    IVector3& IVector3::operator*=(const IVector3& vec)
    {
        this->data[0] *= vec[0];
        this->data[1] *= vec[1];
        this->data[2] *= vec[2];
        return *this;
    }

    IVector3& IVector3::operator/=(const int value)
    {
        this->data[0] /= value;
        this->data[1] /= value;
        this->data[2] /= value;
        return *this;
    }

    IVector3& IVector3::operator/=(const int arr[3])
    {
        this->data[0] /= arr[0];
        this->data[1] /= arr[1];
        this->data[2] /= arr[2];
        return *this;
    }

    IVector3& IVector3::operator/=(const IVector3& vec)
    {
        this->data[0] /= vec[0];
        this->data[1] /= vec[1];
        this->data[2] /= vec[2];
        return *this;
    }

    bool IVector3::operator==(const int value)
    {
        return this->data[0] == value &&
               this->data[1] == value &&
               this->data[2] == value;
    }

    bool IVector3::operator==(const int arr[3])
    {
        return this->data[0] == arr[0] &&
               this->data[1] == arr[1] &&
               this->data[2] == arr[2];
    }

    bool IVector3::operator==(const IVector3& vec)
    {
        return this->data[0] == vec[0] &&
               this->data[1] == vec[1] &&
               this->data[2] == vec[2];
    }

    int& IVector3::operator[](const size_t index)
    {
        return this->data[index];
    }

    const int& IVector3::operator[](const size_t index) const
    {
        return this->data[index];
    }

    int& IVector3::X()
    {
        return this->data[0];
    }

    const int& IVector3::X() const
    {
        return this->data[0];
    }

    int& IVector3::Y()
    {
        return this->data[1];
    }

    const int& IVector3::Y() const
    {
        return this->data[1];
    }

    int& IVector3::Z()
    {
        return this->data[2];
    }

    const int& IVector3::Z() const
    {
        return this->data[2];
    }

    int IVector3::Dot(const IVector3& vec) const
    {
        return (this->data[0] * vec[0]) +
               (this->data[1] * vec[1]) +
               (this->data[2] * vec[2]);
    }

    IVector3 IVector3::Cross(const IVector3& vec) const
    {
        return IVector3((this->data[1] * vec[2]) - (vec[1] * this->data[2]),
                        (this->data[2] * vec[0]) - (vec[2] * this->data[0]),
                        (this->data[0] * vec[1]) - (vec[0] * this->data[1]));
    }

    float IVector3::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]) +
                    (this->data[2] * this->data[2]));
    }

    Vector3 IVector3::Normalize() const
    {
        return Vector3(this->data[0] / this->Length(),
                       this->data[1] / this->Length(),
                       this->data[2] / this->Length());
    }

    float IVector3::Distance(const IVector3& vec) const
    {
        return (*this - vec).Length();
    }
}