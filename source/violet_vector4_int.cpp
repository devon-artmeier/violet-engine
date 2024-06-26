#include "violet_engine_internal.hpp"

namespace Violet
{
    IVector4::IVector4(const int value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
        this->data[3] = value;
    }

    IVector4::IVector4(const int arr[4])
    {
        this->data[0] = arr[0];
        this->data[1] = arr[1];
        this->data[2] = arr[2];
        this->data[3] = arr[3];
    }

    IVector4::IVector4(const int x, const int y, const int z, const int w)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
        this->data[3] = w;
    }

    IVector4::IVector4(const IVector2& vec, const int z, const int w)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = z;
        this->data[3] = w;
    }

    IVector4::IVector4(const IVector3& vec, const int w)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = vec[2];
        this->data[3] = w;
    }

    IVector4::IVector4(const IVector4& vec)
    {
        this->data[0] = vec[0];
        this->data[1] = vec[1];
        this->data[2] = vec[2];
        this->data[3] = vec[3];
    }

    IVector4::operator Vector4() const
    {
        return Vector4(this->data[0], this->data[1], this->data[2], this->data[3]);
    }

    IVector4::operator UIVector4() const
    {
        return UIVector4(this->data[0], this->data[1], this->data[2], this->data[3]);
    }

    IVector4 IVector4::operator+(const IVector4& vec) const
    {
        return IVector4(this->data[0] + vec[0],
                        this->data[1] + vec[1],
                        this->data[2] + vec[2],
                        this->data[3] + vec[3]);
    }

    IVector4 IVector4::operator-(const IVector4& vec) const
    {
        return IVector4(this->data[0] - vec[0],
                        this->data[1] - vec[1],
                        this->data[2] - vec[2],
                        this->data[3] - vec[3]);
    }

    IVector4 IVector4::operator*(const IVector4& vec) const
    {
        return IVector4(this->data[0] * vec[0],
                        this->data[1] * vec[1],
                        this->data[2] * vec[2],
                        this->data[3] * vec[3]);
    }

    IVector4 IVector4::operator/(const IVector4& vec) const
    {
        return IVector4(this->data[0] / vec[0],
                        this->data[1] / vec[1],
                        this->data[2] / vec[2],
                        this->data[3] / vec[3]);
    }

    IVector4& IVector4::operator+=(const IVector4& vec)
    {
        this->data[0] += vec[0];
        this->data[1] += vec[1];
        this->data[2] += vec[2];
        this->data[3] += vec[3];
        return *this;
    }

    IVector4& IVector4::operator-=(const IVector4& vec)
    {
        this->data[0] -= vec[0];
        this->data[1] -= vec[1];
        this->data[2] -= vec[2];
        this->data[3] -= vec[3];
        return *this;
    }

    IVector4& IVector4::operator*=(const IVector4& vec)
    {
        this->data[0] *= vec[0];
        this->data[1] *= vec[1];
        this->data[2] *= vec[2];
        this->data[3] *= vec[3];
        return *this;
    }

    IVector4& IVector4::operator/=(const IVector4& vec)
    {
        this->data[0] /= vec[0];
        this->data[1] /= vec[1];
        this->data[2] /= vec[2];
        this->data[3] /= vec[3];
        return *this;
    }

    bool IVector4::operator==(const IVector4& vec)
    {
        return this->data[0] == vec[0] &&
               this->data[1] == vec[1] &&
               this->data[2] == vec[2] &&
               this->data[3] == vec[3];
    }

    int& IVector4::operator[](const size_t index)
    {
        return this->data[index];
    }

    const int& IVector4::operator[](const size_t index) const
    {
        return this->data[index];
    }

    int& IVector4::X()
    {
        return this->data[0];
    }

    const int& IVector4::X() const
    {
        return this->data[0];
    }

    int& IVector4::Y()
    {
        return this->data[1];
    }

    const int& IVector4::Y() const
    {
        return this->data[1];
    }

    int& IVector4::Z()
    {
        return this->data[2];
    }

    const int& IVector4::Z() const
    {
        return this->data[2];
    }

    int& IVector4::W()
    {
        return this->data[3];
    }

    const int& IVector4::W() const
    {
        return this->data[3];
    }

    int& IVector4::R()
    {
        return this->data[0];
    }

    const int& IVector4::R() const
    {
        return this->data[0];
    }

    int& IVector4::G()
    {
        return this->data[1];
    }

    const int& IVector4::G() const
    {
        return this->data[1];
    }

    int& IVector4::B()
    {
        return this->data[2];
    }

    const int& IVector4::B() const
    {
        return this->data[2];
    }

    int& IVector4::A()
    {
        return this->data[3];
    }

    const int& IVector4::A() const
    {
        return this->data[3];
    }

    int& IVector4::S()
    {
        return this->data[0];
    }

    const int& IVector4::S() const
    {
        return this->data[0];
    }

    int& IVector4::T()
    {
        return this->data[1];
    }

    const int& IVector4::T() const
    {
        return this->data[1];
    }

    int& IVector4::P()
    {
        return this->data[2];
    }

    const int& IVector4::P() const
    {
        return this->data[2];
    }

    int& IVector4::Q()
    {
        return this->data[3];
    }

    const int& IVector4::Q() const
    {
        return this->data[3];
    }

    int IVector4::Dot(const IVector4& vec) const
    {
        return (this->data[0] * vec[0]) +
               (this->data[1] * vec[1]) +
               (this->data[2] * vec[2]) +
               (this->data[3] * vec[3]);
    }

    float IVector4::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]) +
                    (this->data[2] * this->data[2]) +
                    (this->data[3] * this->data[3]));
    }

    Vector4 IVector4::Normalize() const
    {
        return Vector4(this->data[0] / this->Length(),
                       this->data[1] / this->Length(),
                       this->data[2] / this->Length(),
                       this->data[3] / this->Length());
    }

    float IVector4::Distance(const IVector4& vec) const
    {
        return (*this - vec).Length();
    }
}