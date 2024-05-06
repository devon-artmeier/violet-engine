#include "violet_engine_internal.hpp"

namespace Violet
{
    UIVector4::UIVector4(const uint value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
        this->data[3] = value;
    }

    UIVector4::UIVector4(const uint arr[4])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
        this->data[3] = arr[3];
    }

    UIVector4::UIVector4(const uint x, const uint y, const uint z, const uint w)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
        this->data[3] = w;
    }

    UIVector4::UIVector4(const UIVector2& vec, const uint z, const uint w)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
        this->data[2] = z;
        this->data[3] = w;
    }

    UIVector4::UIVector4(const UIVector3& vec, const uint w)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
        this->data[2] = vec.data[2];
        this->data[3] = w;
    }

    UIVector4::UIVector4(const UIVector4& vec)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
        this->data[2] = vec.data[2];
        this->data[3] = vec.data[3];
    }

    UIVector4::operator Vector4() const
    {
        return Vector4(this->data[0], this->data[1], this->data[2], this->data[3]);
    }

    UIVector4::operator IVector4() const
    {
        return IVector4(this->data[0], this->data[1], this->data[2], this->data[3]);
    }

    UIVector4& UIVector4::operator=(const uint value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
        this->data[3] = value;
        return *this;
    }

    UIVector4& UIVector4::operator=(const uint arr[4])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
        this->data[3] = arr[3];
        return *this;
    }

    UIVector4& UIVector4::operator=(const UIVector4& vec)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
        this->data[2] = vec.data[2];
        this->data[3] = vec.data[3];
        return *this;
    }

    UIVector4 UIVector4::operator+(const uint value) const
    {
        return UIVector4(this->data[0] + value,
                         this->data[1] + value,
                         this->data[2] + value,
                         this->data[3] + value);
    }

    UIVector4 UIVector4::operator+(const uint arr[4]) const
    {
        return UIVector4(this->data[0] + arr[0],
                         this->data[1] + arr[1],
                         this->data[2] + arr[2],
                         this->data[3] + arr[3]);
    }

    UIVector4 UIVector4::operator+(const UIVector4& vec) const
    {
        return UIVector4(this->data[0] + vec.data[0],
                         this->data[1] + vec.data[1],
                         this->data[2] + vec.data[2],
                         this->data[3] + vec.data[3]);
    }

    UIVector4 UIVector4::operator-(const uint value) const
    {
        return UIVector4(this->data[0] - value,
                         this->data[1] - value,
                         this->data[2] - value,
                         this->data[3] - value);
    }

    UIVector4 UIVector4::operator-(const uint arr[4]) const
    {
        return UIVector4(this->data[0] - arr[0],
                         this->data[1] - arr[1],
                         this->data[2] - arr[2],
                         this->data[3] - arr[3]);
    }

    UIVector4 UIVector4::operator-(const UIVector4& vec) const
    {
        return UIVector4(this->data[0] - vec.data[0],
                         this->data[1] - vec.data[1],
                         this->data[2] - vec.data[2],
                         this->data[3] - vec.data[3]);
    }

    UIVector4 UIVector4::operator*(const uint value) const
    {
        return UIVector4(this->data[0] * value,
                         this->data[1] * value,
                         this->data[2] * value,
                         this->data[3] * value);
    }

    UIVector4 UIVector4::operator*(const uint arr[4]) const
    {
        return UIVector4(this->data[0] * arr[0],
                         this->data[1] * arr[1],
                         this->data[2] * arr[2],
                         this->data[3] * arr[3]);
    }

    UIVector4 UIVector4::operator*(const UIVector4& vec) const
    {
        return UIVector4(this->data[0] * vec.data[0],
                         this->data[1] * vec.data[1],
                         this->data[2] * vec.data[2],
                         this->data[3] * vec.data[3]);
    }

    UIVector4 UIVector4::operator*(const Matrix4x4& mat) const
    {
        return UIVector4((this->data[0] * mat.data[0]) + (this->data[1] * mat.data[4]) + (this->data[2] * mat.data[8])  + (this->data[3] * mat.data[12]),
                         (this->data[0] * mat.data[1]) + (this->data[1] * mat.data[5]) + (this->data[2] * mat.data[9])  + (this->data[3] * mat.data[13]),
                         (this->data[0] * mat.data[2]) + (this->data[1] * mat.data[6]) + (this->data[2] * mat.data[10]) + (this->data[3] * mat.data[14]),
                         (this->data[0] * mat.data[3]) + (this->data[1] * mat.data[7]) + (this->data[2] * mat.data[11]) + (this->data[3] * mat.data[15]));
    }

    UIVector4 UIVector4::operator/(const uint value) const
    {
        return UIVector4(this->data[0] / value,
                         this->data[1] / value,
                         this->data[2] / value,
                         this->data[3] / value);
    }

    UIVector4 UIVector4::operator/(const uint arr[4]) const
    {
        return UIVector4(this->data[0] / arr[0],
                         this->data[1] / arr[1],
                         this->data[2] / arr[2],
                         this->data[3] / arr[3]);
    }

    UIVector4 UIVector4::operator/(const UIVector4& vec) const
    {
        return UIVector4(this->data[0] / vec.data[0],
                         this->data[1] / vec.data[1],
                         this->data[2] / vec.data[2],
                         this->data[3] / vec.data[3]);
    }

    UIVector4& UIVector4::operator+=(const uint value)
    {
        this->data[0] += value;
        this->data[1] += value;
        this->data[2] += value;
        this->data[3] += value;
        return *this;
    }

    UIVector4& UIVector4::operator+=(const uint arr[4])
    {
        this->data[0] += arr[0];
        this->data[1] += arr[1];
        this->data[2] += arr[1];
        this->data[3] += arr[1];
        return *this;
    }

    UIVector4& UIVector4::operator+=(const UIVector4& vec)
    {
        this->data[0] += vec.data[0];
        this->data[1] += vec.data[1];
        this->data[2] += vec.data[2];
        this->data[3] += vec.data[3];
        return *this;
    }

    UIVector4& UIVector4::operator-=(const uint value)
    {
        this->data[0] -= value;
        this->data[1] -= value;
        this->data[2] -= value;
        this->data[3] -= value;
        return *this;
    }

    UIVector4& UIVector4::operator-=(const uint arr[4])
    {
        this->data[0] -= arr[0];
        this->data[1] -= arr[1];
        this->data[2] -= arr[2];
        this->data[3] -= arr[3];
        return *this;
    }

    UIVector4& UIVector4::operator-=(const UIVector4& vec)
    {
        this->data[0] -= vec.data[0];
        this->data[1] -= vec.data[1];
        this->data[2] -= vec.data[2];
        this->data[3] -= vec.data[3];
        return *this;
    }

    UIVector4& UIVector4::operator*=(const uint value)
    {
        this->data[0] *= value;
        this->data[1] *= value;
        this->data[2] *= value;
        this->data[3] *= value;
        return *this;
    }

    UIVector4& UIVector4::operator*=(const uint arr[4])
    {
        this->data[0] *= arr[0];
        this->data[1] *= arr[1];
        this->data[2] *= arr[2];
        this->data[3] *= arr[3];
        return *this;
    }

    UIVector4& UIVector4::operator*=(const UIVector4& vec)
    {
        this->data[0] *= vec.data[0];
        this->data[1] *= vec.data[1];
        this->data[2] *= vec.data[2];
        this->data[3] *= vec.data[3];
        return *this;
    }

    UIVector4& UIVector4::operator*=(const Matrix4x4& vec)
    {
        this->data[0] = (this->data[0] * vec.data[0]) + (this->data[1] * vec.data[4]) + (this->data[2] * vec.data[8])  + (this->data[3] * vec.data[12]);
        this->data[1] = (this->data[0] * vec.data[1]) + (this->data[1] * vec.data[5]) + (this->data[2] * vec.data[9])  + (this->data[3] * vec.data[13]);
        this->data[2] = (this->data[0] * vec.data[2]) + (this->data[1] * vec.data[6]) + (this->data[2] * vec.data[10]) + (this->data[3] * vec.data[14]);
        this->data[3] = (this->data[0] * vec.data[3]) + (this->data[1] * vec.data[7]) + (this->data[2] * vec.data[11]) + (this->data[3] * vec.data[15]);
        return *this;
    }

    UIVector4& UIVector4::operator/=(const uint value)
    {
        this->data[0] /= value;
        this->data[1] /= value;
        this->data[2] /= value;
        this->data[3] /= value;
        return *this;
    }

    UIVector4& UIVector4::operator/=(const uint arr[4])
    {
        this->data[0] /= arr[0];
        this->data[1] /= arr[1];
        this->data[2] /= arr[2];
        this->data[3] /= arr[3];
        return *this;
    }

    UIVector4& UIVector4::operator/=(const UIVector4& vec)
    {
        this->data[0] /= vec.data[0];
        this->data[1] /= vec.data[1];
        this->data[2] /= vec.data[2];
        this->data[3] /= vec.data[3];
        return *this;
    }

    bool UIVector4::operator==(const uint value)
    {
        return this->data[0] == value &&
               this->data[1] == value &&
               this->data[2] == value &&
               this->data[3] == value;
    }

    bool UIVector4::operator==(const uint arr[4])
    {
        return this->data[0] == arr[0] &&
               this->data[1] == arr[1] &&
               this->data[2] == arr[2] &&
               this->data[3] == arr[3];
    }

    bool UIVector4::operator==(const UIVector4& vec)
    {
        return this->data[0] == vec.data[0] &&
               this->data[1] == vec.data[1] &&
               this->data[2] == vec.data[2] &&
               this->data[3] == vec.data[3];
    }

    uint& UIVector4::operator[](const size_t index)
    {
        return this->data[index];
    }

    const uint& UIVector4::operator[](const size_t index) const
    {
        return this->data[index];
    }

    uint& UIVector4::X()
    {
        return this->data[0];
    }

    const uint& UIVector4::X() const
    {
        return this->data[0];
    }

    uint& UIVector4::Y()
    {
        return this->data[1];
    }

    const uint& UIVector4::Y() const
    {
        return this->data[1];
    }

    uint& UIVector4::Z()
    {
        return this->data[2];
    }

    const uint& UIVector4::Z() const
    {
        return this->data[2];
    }

    uint& UIVector4::W()
    {
        return this->data[3];
    }

    const uint& UIVector4::W() const
    {
        return this->data[3];
    }

    uint UIVector4::Dot(const UIVector4& vec) const
    {
        return (this->data[0] * vec.data[0]) +
               (this->data[1] * vec.data[1]) +
               (this->data[2] * vec.data[2]) +
               (this->data[3] * vec.data[3]);
    }

    float UIVector4::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]) +
                    (this->data[2] * this->data[2]) +
                    (this->data[3] * this->data[3]));
    }

    Vector4 UIVector4::Normalize() const
    {
        return Vector4(this->data[0] / this->Length(),
                       this->data[1] / this->Length(),
                       this->data[2] / this->Length(),
                       this->data[3] / this->Length());
    }

    float UIVector4::Distance(const UIVector4& vec) const
    {
        return (*this - vec).Length();
    }
}