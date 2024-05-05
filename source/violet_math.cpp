#include "violet_engine_internal.hpp"

namespace Violet
{
    Vector2D::Vector2D(const float value)
    {
        (*this)[0] = value;
        (*this)[1] = value;
    }

    Vector2D::Vector2D(const float x, const float y)
    {
        (*this)[0] = x;
        (*this)[1] = y;
    }

    Vector2D::Vector2D(const Vector2D& other)
    {
        (*this)[0] = other[0];
        (*this)[1] = other[1];
    }

    Vector2D& Vector2D::operator=(const float value)
    {
        (*this)[0] = value;
        (*this)[1] = value;
        return *this;
    }

    Vector2D& Vector2D::operator=(const Vector2D& other)
    {
        (*this)[0] = other[0];
        (*this)[1] = other[1];
        return *this;
    }

    Vector2D Vector2D::operator+(const float value) const
    {
        return Vector2D((*this)[0] + value,
                        (*this)[1] + value);
    }

    Vector2D Vector2D::operator+(const Vector2D& other) const
    {
        return Vector2D((*this)[0] + other[0],
                        (*this)[1] + other[1]);
    }

    Vector2D Vector2D::operator-(const float value) const
    {
        return Vector2D((*this)[0] - value,
                        (*this)[1] - value);
    }

    Vector2D Vector2D::operator-(const Vector2D& other) const
    {
        return Vector2D((*this)[0] - other[0],
                        (*this)[1] - other[1]);
    }

    Vector2D Vector2D::operator*(const float value) const
    {
        return Vector2D((*this)[0] * value,
                        (*this)[1] * value);
    }

    Vector2D Vector2D::operator*(const Vector2D& other) const
    {
        return Vector2D((*this)[0] * other[0],
                        (*this)[1] * other[1]);
    }

    Vector2D Vector2D::operator/(const float value) const
    {
        return Vector2D((*this)[0] / value,
                        (*this)[1] / value);
    }

    Vector2D Vector2D::operator/(const Vector2D& other) const
    {
        return Vector2D((*this)[0] / other[0],
                        (*this)[1] / other[1]);
    }

    Vector2D& Vector2D::operator+=(const float value)
    {
        (*this)[0] += value;
        (*this)[1] += value;
        return *this;
    }

    Vector2D& Vector2D::operator+=(const Vector2D& other)
    {
        (*this)[0] += other[0];
        (*this)[1] += other[1];
        return *this;
    }

    Vector2D& Vector2D::operator-=(const float value)
    {
        (*this)[0] -= value;
        (*this)[1] -= value;
        return *this;
    }

    Vector2D& Vector2D::operator-=(const Vector2D& other)
    {
        (*this)[0] -= other[0];
        (*this)[1] -= other[1];
        return *this;
    }

    Vector2D& Vector2D::operator*=(const float value)
    {
        (*this)[0] *= value;
        (*this)[1] *= value;
        return *this;
    }

    Vector2D& Vector2D::operator*=(const Vector2D& other)
    {
        (*this)[0] *= other[0];
        (*this)[1] *= other[1];
        return *this;
    }

    Vector2D& Vector2D::operator/=(const float value)
    {
        (*this)[0] /= value;
        (*this)[1] /= value;
        return *this;
    }

    Vector2D& Vector2D::operator/=(const Vector2D& other)
    {
        (*this)[0] /= other[0];
        (*this)[1] /= other[1];
        return *this;
    }

    float& Vector2D::operator[](const size_t index)
    {
        return (*this)[index];
    }

    const float& Vector2D::operator[](const size_t index) const
    {
        return (*this)[index];
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

    float* Vector2D::Linear()
    {
        return this->data;
    }

    float Vector2D::Dot(const Vector2D& other) const
    {
        return ((*this)[0] * other[0]) +
               ((*this)[1] * other[1]);
    }

    float Vector2D::Length() const
    {
        return sqrt(((*this)[0] * (*this)[0]) +
                    ((*this)[1] * (*this)[1]));
    }

    Vector2D Vector2D::Normalize() const
    {
        return Vector2D((*this)[0] / this->Length(),
                        (*this)[1] / this->Length());
    }

    float Vector2D::Distance(const Vector2D& other) const
    {
        return (*this - other).Length();
    }

    Vector3D::Vector3D(const float value)
    {
        (*this)[0] = value;
        (*this)[1] = value;
        (*this)[2] = value;
    }

    Vector3D::Vector3D(const float x, const float y, const float z)
    {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
    }

    Vector3D::Vector3D(const Vector2D& other, const float z)
    {
        (*this)[0] = other[0];
        (*this)[1] = other[1];
        (*this)[2] = z;
    }

    Vector3D::Vector3D(const Vector3D& other)
    {
        (*this)[0] = other[0];
        (*this)[1] = other[1];
        (*this)[2] = other[2];
    }

    Vector3D& Vector3D::operator=(const float value)
    {
        (*this)[0] = value;
        (*this)[1] = value;
        (*this)[2] = value;
        return *this;
    }

    Vector3D& Vector3D::operator=(const Vector3D& other)
    {
        (*this)[0] = other[0];
        (*this)[1] = other[1];
        (*this)[2] = other[2];
        return *this;
    }

    Vector3D Vector3D::operator+(const float value) const
    {
        return Vector3D((*this)[0] + value,
                        (*this)[1] + value,
                        (*this)[2] + value);
    }

    Vector3D Vector3D::operator+(const Vector3D& other) const
    {
        return Vector3D((*this)[0] + other[0],
                        (*this)[1] + other[1],
                        (*this)[2] + other[2]);
    }

    Vector3D Vector3D::operator-(const float value) const
    {
        return Vector3D((*this)[0] - value,
                        (*this)[1] - value,
                        (*this)[2] - value);
    }

    Vector3D Vector3D::operator-(const Vector3D& other) const
    {
        return Vector3D((*this)[0] - other[0],
                        (*this)[1] - other[1],
                        (*this)[2] - other[2]);
    }

    Vector3D Vector3D::operator*(const float value) const
    {
        return Vector3D((*this)[0] * value,
                        (*this)[1] * value,
                        (*this)[2] * value);
    }

    Vector3D Vector3D::operator*(const Vector3D& other) const
    {
        return Vector3D((*this)[0] * other[0],
                        (*this)[1] * other[1],
                        (*this)[2] * other[2]);
    }

    Vector3D Vector3D::operator/(const float value) const
    {
        return Vector3D((*this)[0] / value,
                        (*this)[1] / value,
                        (*this)[2] / value);
    }

    Vector3D Vector3D::operator/(const Vector3D& other) const
    {
        return Vector3D((*this)[0] / other[0],
                        (*this)[1] / other[1],
                        (*this)[2] / other[2]);
    }

    Vector3D& Vector3D::operator+=(const float value)
    {
        (*this)[0] += value;
        (*this)[1] += value;
        (*this)[2] += value;
        return *this;
    }

    Vector3D& Vector3D::operator+=(const Vector3D& other)
    {
        (*this)[0] += other[0];
        (*this)[1] += other[1];
        (*this)[2] += other[2];
        return *this;
    }

    Vector3D& Vector3D::operator-=(const float value)
    {
        (*this)[0] -= value;
        (*this)[1] -= value;
        (*this)[2] -= value;
        return *this;
    }

    Vector3D& Vector3D::operator-=(const Vector3D& other)
    {
        (*this)[0] -= other[0];
        (*this)[1] -= other[1];
        (*this)[2] -= other[2];
        return *this;
    }

    Vector3D& Vector3D::operator*=(const float value)
    {
        (*this)[0] *= value;
        (*this)[1] *= value;
        (*this)[2] *= value;
        return *this;
    }

    Vector3D& Vector3D::operator*=(const Vector3D& other)
    {
        (*this)[0] *= other[0];
        (*this)[1] *= other[1];
        (*this)[2] *= other[2];
        return *this;
    }

    Vector3D& Vector3D::operator/=(const float value)
    {
        (*this)[0] /= value;
        (*this)[1] /= value;
        (*this)[2] /= value;
        return *this;
    }

    Vector3D& Vector3D::operator/=(const Vector3D& other)
    {
        (*this)[0] /= other[0];
        (*this)[1] /= other[1];
        (*this)[2] /= other[2];
        return *this;
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

    float* Vector3D::Linear()
    {
        return this->data;
    }

    float Vector3D::Dot(const Vector3D& other) const
    {
        return ((*this)[0] * other[0]) +
               ((*this)[1] * other[1]) +
               ((*this)[2] * other[2]);
    }

    Vector3D Vector3D::Cross(const Vector3D& other) const
    {
        return Vector3D(((*this)[1] * other[2]) - (other[1] * (*this)[2]),
                        ((*this)[2] * other[0]) - (other[2] * (*this)[0]),
                        ((*this)[0] * other[1]) - (other[0] * (*this)[1]));
    }

    float Vector3D::Length() const
    {
        return sqrt(((*this)[0] * (*this)[0]) +
                    ((*this)[1] * (*this)[1]) +
                    ((*this)[2] * (*this)[2]));
    }

    Vector3D Vector3D::Normalize() const
    {
        return Vector3D((*this)[0] / this->Length(),
                        (*this)[1] / this->Length(),
                        (*this)[2] / this->Length());
    }

    float Vector3D::Distance(const Vector3D& other) const
    {
        return (*this - other).Length();
    }
    
    Vector4D::Vector4D(const float value)
    {
        (*this)[0] = value;
        (*this)[1] = value;
        (*this)[2] = value;
        (*this)[3] = value;
    }

    Vector4D::Vector4D(const float x, const float y, const float z, const float w)
    {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
        (*this)[3] = w;
    }

    Vector4D::Vector4D(const Vector2D& other, const float z, const float w)
    {
        (*this)[0] = other[0];
        (*this)[1] = other[1];
        (*this)[2] = z;
        (*this)[3] = w;
    }

    Vector4D::Vector4D(const Vector3D& other, const float w)
    {
        (*this)[0] = other[0];
        (*this)[1] = other[1];
        (*this)[2] = other[2];
        (*this)[3] = w;
    }

    Vector4D::Vector4D(const Vector4D& other)
    {
        (*this)[0] = other[0];
        (*this)[1] = other[1];
        (*this)[2] = other[2];
        (*this)[3] = other[3];
    }

    Vector4D& Vector4D::operator=(const float value)
    {
        (*this)[0] = value;
        (*this)[1] = value;
        (*this)[2] = value;
        (*this)[3] = value;
        return *this;
    }

    Vector4D& Vector4D::operator=(const Vector4D& other)
    {
        (*this)[0] = other[0];
        (*this)[1] = other[1];
        (*this)[2] = other[2];
        (*this)[3] = other[3];
        return *this;
    }

    Vector4D Vector4D::operator+(const float value) const
    {
        return Vector4D((*this)[0] + value,
                        (*this)[1] + value,
                        (*this)[2] + value,
                        (*this)[3] + value);
    }

    Vector4D Vector4D::operator+(const Vector4D& other) const
    {
        return Vector4D((*this)[0] + other[0],
                        (*this)[1] + other[1],
                        (*this)[2] + other[2],
                        (*this)[3] + other[3]);
    }

    Vector4D Vector4D::operator-(const float value) const
    {
        return Vector4D((*this)[0] - value,
                        (*this)[1] - value,
                        (*this)[2] - value,
                        (*this)[3] - value);
    }

    Vector4D Vector4D::operator-(const Vector4D& other) const
    {
        return Vector4D((*this)[0] - other[0],
                        (*this)[1] - other[1],
                        (*this)[2] - other[2],
                        (*this)[3] - other[3]);
    }

    Vector4D Vector4D::operator*(const float value) const
    {
        return Vector4D((*this)[0] * value,
                        (*this)[1] * value,
                        (*this)[2] * value,
                        (*this)[3] * value);
    }

    Vector4D Vector4D::operator*(const Vector4D& other) const
    {
        return Vector4D((*this)[0] * other[0],
                        (*this)[1] * other[1],
                        (*this)[2] * other[2],
                        (*this)[3] * other[3]);
    }

    Vector4D Vector4D::operator/(const float value) const
    {
        return Vector4D((*this)[0] / value,
                        (*this)[1] / value,
                        (*this)[2] / value,
                        (*this)[3] / value);
    }

    Vector4D Vector4D::operator/(const Vector4D& other) const
    {
        return Vector4D((*this)[0] / other[0],
                        (*this)[1] / other[1],
                        (*this)[2] / other[2],
                        (*this)[3] / other[3]);
    }

    Vector4D& Vector4D::operator+=(const float value)
    {
        (*this)[0] += value;
        (*this)[1] += value;
        (*this)[2] += value;
        (*this)[3] += value;
        return *this;
    }

    Vector4D& Vector4D::operator+=(const Vector4D& other)
    {
        (*this)[0] += other[0];
        (*this)[1] += other[1];
        (*this)[2] += other[2];
        (*this)[3] += other[3];
        return *this;
    }

    Vector4D& Vector4D::operator-=(const float value)
    {
        (*this)[0] -= value;
        (*this)[1] -= value;
        (*this)[2] -= value;
        (*this)[3] -= value;
        return *this;
    }

    Vector4D& Vector4D::operator-=(const Vector4D& other)
    {
        (*this)[0] -= other[0];
        (*this)[1] -= other[1];
        (*this)[2] -= other[2];
        (*this)[3] -= other[3];
        return *this;
    }

    Vector4D& Vector4D::operator*=(const float value)
    {
        (*this)[0] *= value;
        (*this)[1] *= value;
        (*this)[2] *= value;
        (*this)[3] *= value;
        return *this;
    }

    Vector4D& Vector4D::operator*=(const Vector4D& other)
    {
        (*this)[0] *= other[0];
        (*this)[1] *= other[1];
        (*this)[2] *= other[2];
        (*this)[3] *= other[3];
        return *this;
    }

    Vector4D& Vector4D::operator/=(const float value)
    {
        (*this)[0] /= value;
        (*this)[1] /= value;
        (*this)[2] /= value;
        (*this)[3] /= value;
        return *this;
    }

    Vector4D& Vector4D::operator/=(const Vector4D& other)
    {
        (*this)[0] /= other[0];
        (*this)[1] /= other[1];
        (*this)[2] /= other[2];
        (*this)[3] /= other[3];
        return *this;
    }

    float& Vector4D::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float& Vector4D::operator[](const size_t index) const
    {
        return this->data[index];
    }

    float& Vector4D::X()
    {
        return this->data[0];
    }

    const float& Vector4D::X() const
    {
        return this->data[0];
    }

    float& Vector4D::Y()
    {
        return this->data[1];
    }

    const float& Vector4D::Y() const
    {
        return this->data[1];
    }

    float& Vector4D::Z()
    {
        return this->data[2];
    }

    const float& Vector4D::Z() const
    {
        return this->data[2];
    }

    float& Vector4D::W()
    {
        return this->data[3];
    }

    const float& Vector4D::W() const
    {
        return this->data[3];
    }

    float* Vector4D::Linear()
    {
        return this->data;
    }

    float Vector4D::Dot(const Vector4D& other) const
    {
        return ((*this)[0] * other[0]) + 
               ((*this)[1] * other[1]) +
               ((*this)[2] * other[2]) +
               ((*this)[3] * other[3]);
    }

    float Vector4D::Length() const
    {
        return sqrt(((*this)[0] * (*this)[0]) +
                    ((*this)[1] * (*this)[1]) +
                    ((*this)[2] * (*this)[2]) +
                    ((*this)[3] * (*this)[3]));
    }

    Vector4D Vector4D::Normalize() const
    {
        return Vector4D((*this)[0] / this->Length(),
                        (*this)[1] / this->Length(),
                        (*this)[2] / this->Length(),
                        (*this)[3] / this->Length());
    }

    float Vector4D::Distance(const Vector4D& other) const
    {
        return (*this - other).Length();
    }

    Matrix4x4::Matrix4x4(const float value)
    {
        (*this)[0] = value;
        (*this)[1] = value;
        (*this)[2] = value;
        (*this)[3] = value;
    }

    Matrix4x4::Matrix4x4(const Vector4D& data1, const Vector4D& data2, const Vector4D& data3, const Vector4D& data4)
    {
        (*this)[0] = data1;
        (*this)[1] = data2;
        (*this)[2] = data3;
        (*this)[3] = data4;
    }

    Vector4D Matrix4x4::operator*(const Vector4D& other) const
    {
        return Vector4D(
            ((*this)[0][0] * other[0]) + ((*this)[1][0] * other[1]) + ((*this)[2][0] * other[2]) + ((*this)[3][0] * other[3]),
            ((*this)[0][1] * other[0]) + ((*this)[1][1] * other[1]) + ((*this)[2][1] * other[2]) + ((*this)[3][1] * other[3]),
            ((*this)[0][2] * other[0]) + ((*this)[1][2] * other[1]) + ((*this)[2][2] * other[2]) + ((*this)[3][2] * other[3]),
            ((*this)[0][3] * other[0]) + ((*this)[1][3] * other[1]) + ((*this)[2][3] * other[2]) + ((*this)[3][3] * other[3])
        );
    }

    Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
    {
        return Matrix4x4(
            Vector4D(((*this)[0][0] * other[0][0]) + ((*this)[1][0] * other[0][1]) + ((*this)[2][0] * other[0][2]) + ((*this)[3][0] * other[0][3]),
                     ((*this)[0][1] * other[0][0]) + ((*this)[1][1] * other[0][1]) + ((*this)[2][1] * other[0][2]) + ((*this)[3][1] * other[0][3]),
                     ((*this)[0][2] * other[0][0]) + ((*this)[1][2] * other[0][1]) + ((*this)[2][2] * other[0][2]) + ((*this)[3][2] * other[0][3]),
                     ((*this)[0][3] * other[0][0]) + ((*this)[1][3] * other[0][1]) + ((*this)[2][3] * other[0][2]) + ((*this)[3][3] * other[0][3])),
            Vector4D(((*this)[0][0] * other[1][0]) + ((*this)[1][0] * other[1][1]) + ((*this)[2][0] * other[1][2]) + ((*this)[3][0] * other[1][3]),
                     ((*this)[0][1] * other[1][0]) + ((*this)[1][1] * other[1][1]) + ((*this)[2][1] * other[1][2]) + ((*this)[3][1] * other[1][3]),
                     ((*this)[0][2] * other[1][0]) + ((*this)[1][2] * other[1][1]) + ((*this)[2][2] * other[1][2]) + ((*this)[3][2] * other[1][3]),
                     ((*this)[0][3] * other[1][0]) + ((*this)[1][3] * other[1][1]) + ((*this)[2][3] * other[1][2]) + ((*this)[3][3] * other[1][3])),
            Vector4D(((*this)[0][0] * other[2][0]) + ((*this)[1][0] * other[2][1]) + ((*this)[2][0] * other[2][2]) + ((*this)[3][0] * other[2][3]),
                     ((*this)[0][1] * other[2][0]) + ((*this)[1][1] * other[2][1]) + ((*this)[2][1] * other[2][2]) + ((*this)[3][1] * other[2][3]),
                     ((*this)[0][2] * other[2][0]) + ((*this)[1][2] * other[2][1]) + ((*this)[2][2] * other[2][2]) + ((*this)[3][2] * other[2][3]),
                     ((*this)[0][3] * other[2][0]) + ((*this)[1][3] * other[2][1]) + ((*this)[2][3] * other[2][2]) + ((*this)[3][3] * other[2][3])),
            Vector4D(((*this)[0][0] * other[3][0]) + ((*this)[1][0] * other[3][1]) + ((*this)[2][0] * other[3][2]) + ((*this)[3][0] * other[3][3]),
                     ((*this)[0][1] * other[3][0]) + ((*this)[1][1] * other[3][1]) + ((*this)[2][1] * other[3][2]) + ((*this)[3][1] * other[3][3]),
                     ((*this)[0][2] * other[3][0]) + ((*this)[1][2] * other[3][1]) + ((*this)[2][2] * other[3][2]) + ((*this)[3][2] * other[3][3]),
                     ((*this)[0][3] * other[3][0]) + ((*this)[1][3] * other[3][1]) + ((*this)[2][3] * other[3][2]) + ((*this)[3][3] * other[3][3]))
        );
    }

    Vector4D& Matrix4x4::operator[](const size_t index)
    {
        return (*this)[index];
    }

    const Vector4D& Matrix4x4::operator[](const size_t index) const
    {
        return (*this)[index];
    }

    namespace Math
    {
        float Sin(const float angle)
        {
            return sinf(angle);
        }

        double Sin(const double angle)
        {
            return sin(angle);
        }

        float Cos(const float angle)
        {
            return cosf(angle);
        }

        double Cos(const double angle)
        {
            return cos(angle);
        }

        float SinDeg(const float angle)
        {
            return sinf(DegToRad(angle));
        }

        double SinDeg(const double angle)
        {
            return sin(DegToRad(angle));
        }

        float CosDeg(const float angle)
        {
            return cosf(DegToRad(angle));
        }

        double CosDeg(const double angle)
        {
            return cos(DegToRad(angle));
        }

        float DegToRad(const float degrees)
        {
            return degrees * (static_cast<float>(Pi) / 180.0f);
        }

        double DegToRad(const double degrees)
        {
            return degrees * (Pi / 180.0);
        }

        float RadToDeg(const float radians)
        {
            return radians * (180.0f / static_cast<float>(Pi));
        }

        double RadToDeg(const double radians)
        {
            return radians * (180.0 / Pi);
        }
    }
}