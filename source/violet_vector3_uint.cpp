#include "violet_engine_internal.hpp"

namespace Violet
{
    UIVector3::UIVector3(const uint value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
    }

    UIVector3::UIVector3(const uint arr[3])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
    }

    UIVector3::UIVector3(const uint x, const uint y, const uint z)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
    }

    UIVector3::UIVector3(const UIVector2& vec, const uint z)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = z;
    }

    UIVector3::UIVector3(const UIVector3& vec)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = vec[2];
    }

    UIVector3::operator Vector3() const
    {
        return Vector3(this->data[0], this->data[1], this->data[2]);
    }

    UIVector3::operator IVector3() const
    {
        return IVector3(this->data[0], this->data[1], this->data[2]);
    }

    UIVector3& UIVector3::operator=(const uint value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
        return *this;
    }

    UIVector3& UIVector3::operator=(const uint arr[3])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
        return *this;
    }

    UIVector3& UIVector3::operator=(const UIVector3& vec)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = vec[2];
        return *this;
    }

    UIVector3 UIVector3::operator+(const uint value) const
    {
        return UIVector3(this->data[0] + value,
                         this->data[1] + value,
                         this->data[2] + value);
    }

    UIVector3 UIVector3::operator+(const uint arr[3]) const
    {
        return UIVector3(this->data[0] + arr[0],
                         this->data[1] + arr[1],
                         this->data[2] + arr[2]);
    }

    UIVector3 UIVector3::operator+(const UIVector3& vec) const
    {
        return UIVector3(this->data[0] + vec[0],
                         this->data[1] + vec[1],
                         this->data[2] + vec[2]);
    }

    UIVector3 UIVector3::operator-(const uint value) const
    {
        return UIVector3(this->data[0] - value,
                         this->data[1] - value,
                         this->data[2] - value);
    }

    UIVector3 UIVector3::operator-(const uint arr[3]) const
    {
        return UIVector3(this->data[0] - arr[0],
                         this->data[1] - arr[1],
                         this->data[2] - arr[2]);
    }

    UIVector3 UIVector3::operator-(const UIVector3& vec) const
    {
        return UIVector3(this->data[0] - vec[0],
                         this->data[1] - vec[1],
                         this->data[2] - vec[2]);
    }

    UIVector3 UIVector3::operator*(const uint value) const
    {
        return UIVector3(this->data[0] * value,
                         this->data[1] * value,
                         this->data[2] * value);
    }

    UIVector3 UIVector3::operator*(const uint arr[3]) const
    {
        return UIVector3(this->data[0] * arr[0],
                         this->data[1] * arr[1],
                         this->data[2] * arr[2]);
    }

    UIVector3 UIVector3::operator*(const UIVector3& vec) const
    {
        return UIVector3(this->data[0] * vec[0],
                         this->data[1] * vec[1],
                         this->data[2] * vec[2]);
    }

    UIVector3 UIVector3::operator*(const Matrix3x3& mat) const
    {
        return UIVector3((this->data[0] * mat[0][0]) + (this->data[1] * mat[1][0]) + (this->data[2] * mat[2][0]),
                         (this->data[0] * mat[0][1]) + (this->data[1] * mat[1][1]) + (this->data[2] * mat[2][1]),
                         (this->data[0] * mat[0][2]) + (this->data[1] * mat[1][2]) + (this->data[2] * mat[2][2]));
    }

    UIVector3 UIVector3::operator/(const uint value) const
    {
        return UIVector3(this->data[0] / value,
                         this->data[1] / value,
                         this->data[2] / value);
    }

    UIVector3 UIVector3::operator/(const uint arr[3]) const
    {
        return UIVector3(this->data[0] / arr[0],
                         this->data[1] / arr[1],
                         this->data[2] / arr[2]);
    }

    UIVector3 UIVector3::operator/(const UIVector3& vec) const
    {
        return UIVector3(this->data[0] / vec[0],
                         this->data[1] / vec[1],
                         this->data[2] / vec[2]);
    }

    UIVector3& UIVector3::operator+=(const uint value)
    {
        this->data[0] += value;
        this->data[1] += value;
        this->data[2] += value;
        return *this;
    }

    UIVector3& UIVector3::operator+=(const uint arr[3])
    {
        this->data[0] += arr[0];
        this->data[1] += arr[1];
        this->data[2] += arr[2];
        return *this;
    }

    UIVector3& UIVector3::operator+=(const UIVector3& vec)
    {
        this->data[0] += vec[0];
        this->data[1] += vec[1];
        this->data[2] += vec[2];
        return *this;
    }

    UIVector3& UIVector3::operator-=(const uint value)
    {
        this->data[0] -= value;
        this->data[1] -= value;
        this->data[2] -= value;
        return *this;
    }

    UIVector3& UIVector3::operator-=(const uint arr[3])
    {
        this->data[0] -= arr[0];
        this->data[1] -= arr[1];
        this->data[2] -= arr[2];
        return *this;
    }

    UIVector3& UIVector3::operator-=(const UIVector3& vec)
    {
        this->data[0] -= vec[0];
        this->data[1] -= vec[1];
        this->data[2] -= vec[2];
        return *this;
    }

    UIVector3& UIVector3::operator*=(const uint value)
    {
        this->data[0] *= value;
        this->data[1] *= value;
        this->data[2] *= value;
        return *this;
    }

    UIVector3& UIVector3::operator*=(const uint arr[3])
    {
        this->data[0] *= arr[0];
        this->data[1] *= arr[1];
        this->data[2] *= arr[2];
        return *this;
    }

    UIVector3& UIVector3::operator*=(const UIVector3& vec)
    {
        this->data[0] *= vec[0];
        this->data[1] *= vec[1];
        this->data[2] *= vec[2];
        return *this;
    }

    UIVector3& UIVector3::operator*=(const Matrix3x3& mat)
    {
        this->data[0] = (this->data[0] * mat[0][0]) + (this->data[1] * mat[1][0]) + (this->data[2] * mat[2][0]);
        this->data[1] = (this->data[0] * mat[0][1]) + (this->data[1] * mat[1][1]) + (this->data[2] * mat[2][1]);
        this->data[2] = (this->data[0] * mat[0][2]) + (this->data[1] * mat[1][2]) + (this->data[2] * mat[2][2]);
        return *this;
    }

    UIVector3& UIVector3::operator/=(const uint value)
    {
        this->data[0] /= value;
        this->data[1] /= value;
        this->data[2] /= value;
        return *this;
    }

    UIVector3& UIVector3::operator/=(const uint arr[3])
    {
        this->data[0] /= arr[0];
        this->data[1] /= arr[1];
        this->data[2] /= arr[2];
        return *this;
    }

    UIVector3& UIVector3::operator/=(const UIVector3& vec)
    {
        this->data[0] /= vec[0];
        this->data[1] /= vec[1];
        this->data[2] /= vec[2];
        return *this;
    }

    bool UIVector3::operator==(const uint value)
    {
        return this->data[0] == value &&
               this->data[1] == value &&
               this->data[2] == value;
    }

    bool UIVector3::operator==(const uint arr[3])
    {
        return this->data[0] == arr[0] &&
               this->data[1] == arr[1] &&
               this->data[2] == arr[2];
    }

    bool UIVector3::operator==(const UIVector3& vec)
    {
        return this->data[0] == vec[0] &&
               this->data[1] == vec[1] &&
               this->data[2] == vec[2];
    }

    uint& UIVector3::operator[](const size_t index)
    {
        return this->data[index];
    }

    const uint& UIVector3::operator[](const size_t index) const
    {
        return this->data[index];
    }

    uint& UIVector3::X()
    {
        return this->data[0];
    }

    const uint& UIVector3::X() const
    {
        return this->data[0];
    }

    uint& UIVector3::Y()
    {
        return this->data[1];
    }

    const uint& UIVector3::Y() const
    {
        return this->data[1];
    }

    uint& UIVector3::Z()
    {
        return this->data[2];
    }

    const uint& UIVector3::Z() const
    {
        return this->data[2];
    }

    uint UIVector3::Dot(const UIVector3& vec) const
    {
        return (this->data[0] * vec[0]) +
               (this->data[1] * vec[1]) +
               (this->data[2] * vec[2]);
    }

    UIVector3 UIVector3::Cross(const UIVector3& vec) const
    {
        return UIVector3((this->data[1] * vec[2]) - (vec[1] * this->data[2]),
                         (this->data[2] * vec[0]) - (vec[2] * this->data[0]),
                         (this->data[0] * vec[1]) - (vec[0] * this->data[1]));
    }

    float UIVector3::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]) +
                    (this->data[2] * this->data[2]));
    }

    Vector3 UIVector3::Normalize() const
    {
        return Vector3(this->data[0] / this->Length(),
                       this->data[1] / this->Length(),
                       this->data[2] / this->Length());
    }

    float UIVector3::Distance(const UIVector3& vec) const
    {
        return (*this - vec).Length();
    }
}