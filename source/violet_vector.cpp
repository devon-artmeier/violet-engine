#include "violet_engine_internal.hpp"

namespace Violet
{
    Vector2D::Vector2D(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
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

    Vector2D& Vector2D::operator=(const Vector2D& other)
    {
        this->data[0] = other.data[0];
        this->data[1] = other.data[1];
        return *this;
    }

    Vector2D Vector2D::operator+(const float value) const
    {
        Vector2D vec;
        vec.data[0] = this->data[0] + value;
        vec.data[1] = this->data[1] + value;
        return vec;
    }

    Vector2D Vector2D::operator+(const Vector2D& other) const
    {
        Vector2D vec;
        vec.data[0] = this->data[0] + other.data[0];
        vec.data[1] = this->data[1] + other.data[1];
        return vec;
    }

    Vector2D Vector2D::operator-(const float value) const
    {
        Vector2D vec;
        vec.data[0] = this->data[0] - value;
        vec.data[1] = this->data[1] - value;
        return vec;
    }

    Vector2D Vector2D::operator-(const Vector2D& other) const
    {
        Vector2D vec;
        vec.data[0] = this->data[0] - other.data[0];
        vec.data[1] = this->data[1] - other.data[1];
        return vec;
    }

    Vector2D Vector2D::operator*(const float value) const
    {
        Vector2D vec;
        vec.data[0] = this->data[0] * value;
        vec.data[1] = this->data[1] * value;
        return vec;
    }

    Vector2D Vector2D::operator*(const Vector2D& other) const
    {
        Vector2D vec;
        vec.data[0] = this->data[0] * other.data[0];
        vec.data[1] = this->data[1] * other.data[1];
        return vec;
    }

    Vector2D Vector2D::operator/(const float value) const
    {
        Vector2D vec;
        vec.data[0] = this->data[0] / value;
        vec.data[1] = this->data[1] / value;
        return vec;
    }

    Vector2D Vector2D::operator/(const Vector2D& other) const
    {
        Vector2D vec;
        vec.data[0] = this->data[0] / other.data[0];
        vec.data[1] = this->data[1] / other.data[1];
        return vec;
    }

    Vector2D& Vector2D::operator+=(const float value)
    {
        this->data[0] += value;
        this->data[1] += value;
        return *this;
    }

    Vector2D& Vector2D::operator+=(const Vector2D& other)
    {
        this->data[0] += other.data[0];
        this->data[1] += other.data[1];
        return *this;
    }

    Vector2D& Vector2D::operator-=(const float value)
    {
        this->data[0] -= value;
        this->data[1] -= value;
        return *this;
    }

    Vector2D& Vector2D::operator-=(const Vector2D& other)
    {
        this->data[0] -= other.data[0];
        this->data[1] -= other.data[1];
        return *this;
    }

    Vector2D& Vector2D::operator*=(const float value)
    {
        this->data[0] *= value;
        this->data[1] *= value;
        return *this;
    }

    Vector2D& Vector2D::operator*=(const Vector2D& other)
    {
        this->data[0] *= other.data[0];
        this->data[1] *= other.data[1];
        return *this;
    }

    Vector2D& Vector2D::operator/=(const float value)
    {
        this->data[0] /= value;
        this->data[1] /= value;
        return *this;
    }

    Vector2D& Vector2D::operator/=(const Vector2D& other)
    {
        this->data[0] /= other.data[0];
        this->data[1] /= other.data[1];
        return *this;
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

    float Vector2D::Dot(const Vector2D& other) const
    {
        return (this->data[0] * other.data[0]) +
               (this->data[1] * other.data[1]);
    }

    float Vector2D::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]));
    }

    Vector2D Vector2D::Normalize() const
    {
        Vector2D vec;
        vec.data[0] = this->data[0] / this->Length();
        vec.data[1] = this->data[1] / this->Length();
        return vec;
    }

    float Vector2D::Distance(const Vector2D& other) const
    {
        return (*this - other).Length();
    }

    Vector3D::Vector3D(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
    }

    Vector3D::Vector3D(const float x, const float y, const float z)
    {
        this->data[0] = x;
        this->data[1] = y;
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

    Vector3D& Vector3D::operator=(const Vector3D& other)
    {
        this->data[0] = other.data[0];
        this->data[1] = other.data[1];
        this->data[2] = other.data[2];
        return *this;
    }

    Vector3D Vector3D::operator+(const float value) const
    {
        Vector3D vec;
        vec.data[0] = this->data[0] + value;
        vec.data[1] = this->data[1] + value;
        vec.data[2] = this->data[2] + value;
        return vec;
    }

    Vector3D Vector3D::operator+(const Vector3D& other) const
    {
        Vector3D vec;
        vec.data[0] = this->data[0] + other.data[0];
        vec.data[1] = this->data[1] + other.data[1];
        vec.data[2] = this->data[2] + other.data[2];
        return vec;
    }

    Vector3D Vector3D::operator-(const float value) const
    {
        Vector3D vec;
        vec.data[0] = this->data[0] - value;
        vec.data[1] = this->data[1] - value;
        vec.data[2] = this->data[2] - value;
        return vec;
    }

    Vector3D Vector3D::operator-(const Vector3D& other) const
    {
        Vector3D vec;
        vec.data[0] = this->data[0] - other.data[0];
        vec.data[1] = this->data[1] - other.data[1];
        vec.data[2] = this->data[2] - other.data[2];
        return vec;
    }

    Vector3D Vector3D::operator*(const float value) const
    {
        Vector3D vec;
        vec.data[0] = this->data[0] * value;
        vec.data[1] = this->data[1] * value;
        vec.data[2] = this->data[2] * value;
        return vec;
    }

    Vector3D Vector3D::operator*(const Vector3D& other) const
    {
        Vector3D vec;
        vec.data[0] = this->data[0] * other.data[0];
        vec.data[1] = this->data[1] * other.data[1];
        vec.data[2] = this->data[2] * other.data[2];
        return vec;
    }

    Vector3D Vector3D::operator/(const float value) const
    {
        Vector3D vec;
        vec.data[0] = this->data[0] / value;
        vec.data[1] = this->data[1] / value;
        vec.data[2] = this->data[2] / value;
        return vec;
    }

    Vector3D Vector3D::operator/(const Vector3D& other) const
    {
        Vector3D vec;
        vec.data[0] = this->data[0] / other.data[0];
        vec.data[1] = this->data[1] / other.data[1];
        vec.data[2] = this->data[2] / other.data[2];
        return vec;
    }

    Vector3D& Vector3D::operator+=(const float value)
    {
        this->data[0] += value;
        this->data[1] += value;
        this->data[2] += value;
        return *this;
    }

    Vector3D& Vector3D::operator+=(const Vector3D& other)
    {
        this->data[0] += other.data[0];
        this->data[1] += other.data[1];
        this->data[2] += other.data[2];
        return *this;
    }

    Vector3D& Vector3D::operator-=(const float value)
    {
        this->data[0] -= value;
        this->data[1] -= value;
        this->data[2] -= value;
        return *this;
    }

    Vector3D& Vector3D::operator-=(const Vector3D& other)
    {
        this->data[0] -= other.data[0];
        this->data[1] -= other.data[1];
        this->data[2] -= other.data[2];
        return *this;
    }

    Vector3D& Vector3D::operator*=(const float value)
    {
        this->data[0] *= value;
        this->data[1] *= value;
        this->data[2] *= value;
        return *this;
    }

    Vector3D& Vector3D::operator*=(const Vector3D& other)
    {
        this->data[0] *= other.data[0];
        this->data[1] *= other.data[1];
        this->data[2] *= other.data[2];
        return *this;
    }

    Vector3D& Vector3D::operator/=(const float value)
    {
        this->data[0] /= value;
        this->data[1] /= value;
        this->data[2] /= value;
        return *this;
    }

    Vector3D& Vector3D::operator/=(const Vector3D& other)
    {
        this->data[0] /= other.data[0];
        this->data[1] /= other.data[1];
        this->data[2] /= other.data[2];
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

    float Vector3D::Dot(const Vector3D& other) const
    {
        return (this->data[0] * other.data[0]) +
               (this->data[1] * other.data[1]) +
               (this->data[2] * other.data[2]);
    }

    Vector3D Vector3D::Cross(const Vector3D& other) const
    {
        Vector3D vec;
        vec.data[0] = (this->data[1] * other.data[2]) - (other.data[1] * this->data[2]);
        vec.data[1] = (this->data[2] * other.data[0]) - (other.data[2] * this->data[0]);
        vec.data[2] = (this->data[0] * other.data[1]) - (other.data[0] * this->data[1]);
        return vec;
    }

    float Vector3D::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]) +
                    (this->data[2] * this->data[2]));
    }

    Vector3D Vector3D::Normalize() const
    {
        Vector3D vec;
        vec.data[0] = this->data[0] / this->Length();
        vec.data[1] = this->data[1] / this->Length();
        vec.data[2] = this->data[2] / this->Length();
        return vec;
    }

    float Vector3D::Distance(const Vector3D& other) const
    {
        return (*this - other).Length();
    }
    
    Vector4D::Vector4D(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
        this->data[3] = value;
    }

    Vector4D::Vector4D(const float x, const float y, const float z, const float w)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
        this->data[3] = w;
    }

    Vector4D::Vector4D(const Vector4D& vec)
    {
        this->data[0] = vec.data[0];
        this->data[1] = vec.data[1];
        this->data[2] = vec.data[2];
        this->data[3] = vec.data[3];
    }

    Vector4D& Vector4D::operator=(const float value)
    {
        this->data[0] = value;
        this->data[1] = value;
        this->data[2] = value;
        this->data[3] = value;
        return *this;
    }

    Vector4D& Vector4D::operator=(const Vector4D& other)
    {
        this->data[0] = other.data[0];
        this->data[1] = other.data[1];
        this->data[2] = other.data[2];
        this->data[3] = other.data[3];
        return *this;
    }

    Vector4D Vector4D::operator+(const float value) const
    {
        Vector4D vec;
        vec.data[0] = this->data[0] + value;
        vec.data[1] = this->data[1] + value;
        vec.data[2] = this->data[2] + value;
        vec.data[3] = this->data[3] + value;
        return vec;
    }

    Vector4D Vector4D::operator+(const Vector4D& other) const
    {
        Vector4D vec;
        vec.data[0] = this->data[0] + other.data[0];
        vec.data[1] = this->data[1] + other.data[1];
        vec.data[2] = this->data[2] + other.data[2];
        vec.data[3] = this->data[3] + other.data[3];
        return vec;
    }

    Vector4D Vector4D::operator-(const float value) const
    {
        Vector4D vec;
        vec.data[0] = this->data[0] - value;
        vec.data[1] = this->data[1] - value;
        vec.data[2] = this->data[2] - value;
        vec.data[3] = this->data[3] - value;
        return vec;
    }

    Vector4D Vector4D::operator-(const Vector4D& other) const
    {
        Vector4D vec;
        vec.data[0] = this->data[0] - other.data[0];
        vec.data[1] = this->data[1] - other.data[1];
        vec.data[2] = this->data[2] - other.data[2];
        vec.data[3] = this->data[3] - other.data[3];
        return vec;
    }

    Vector4D Vector4D::operator*(const float value) const
    {
        Vector4D vec;
        vec.data[0] = this->data[0] * value;
        vec.data[1] = this->data[1] * value;
        vec.data[2] = this->data[2] * value;
        vec.data[3] = this->data[3] * value;
        return vec;
    }

    Vector4D Vector4D::operator*(const Vector4D& other) const
    {
        Vector4D vec;
        vec.data[0] = this->data[0] * other.data[0];
        vec.data[1] = this->data[1] * other.data[1];
        vec.data[2] = this->data[2] * other.data[2];
        vec.data[3] = this->data[3] * other.data[3];
        return vec;
    }

    Vector4D Vector4D::operator/(const float value) const
    {
        Vector4D vec;
        vec.data[0] = this->data[0] / value;
        vec.data[1] = this->data[1] / value;
        vec.data[2] = this->data[2] / value;
        vec.data[3] = this->data[3] / value;
        return vec;
    }

    Vector4D Vector4D::operator/(const Vector4D& other) const
    {
        Vector4D vec;
        vec.data[0] = this->data[0] / other.data[0];
        vec.data[1] = this->data[1] / other.data[1];
        vec.data[2] = this->data[2] / other.data[2];
        vec.data[3] = this->data[3] / other.data[3];
        return vec;
    }

    Vector4D& Vector4D::operator+=(const float value)
    {
        this->data[0] += value;
        this->data[1] += value;
        this->data[2] += value;
        this->data[3] += value;
        return *this;
    }

    Vector4D& Vector4D::operator+=(const Vector4D& other)
    {
        this->data[0] += other.data[0];
        this->data[1] += other.data[1];
        this->data[2] += other.data[2];
        this->data[3] += other.data[3];
        return *this;
    }

    Vector4D& Vector4D::operator-=(const float value)
    {
        this->data[0] -= value;
        this->data[1] -= value;
        this->data[2] -= value;
        this->data[3] -= value;
        return *this;
    }

    Vector4D& Vector4D::operator-=(const Vector4D& other)
    {
        this->data[0] -= other.data[0];
        this->data[1] -= other.data[1];
        this->data[2] -= other.data[2];
        this->data[3] -= other.data[3];
        return *this;
    }

    Vector4D& Vector4D::operator*=(const float value)
    {
        this->data[0] *= value;
        this->data[1] *= value;
        this->data[2] *= value;
        this->data[3] *= value;
        return *this;
    }

    Vector4D& Vector4D::operator*=(const Vector4D& other)
    {
        this->data[0] *= other.data[0];
        this->data[1] *= other.data[1];
        this->data[2] *= other.data[2];
        this->data[3] *= other.data[3];
        return *this;
    }

    Vector4D& Vector4D::operator/=(const float value)
    {
        this->data[0] /= value;
        this->data[1] /= value;
        this->data[2] /= value;
        this->data[3] /= value;
        return *this;
    }

    Vector4D& Vector4D::operator/=(const Vector4D& other)
    {
        this->data[0] /= other.data[0];
        this->data[1] /= other.data[1];
        this->data[2] /= other.data[2];
        this->data[3] /= other.data[3];
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

    float Vector4D::Dot(const Vector4D& other) const
    {
        return (this->data[0] * other.data[0]) + 
               (this->data[1] * other.data[1]) +
               (this->data[2] * other.data[2]) +
               (this->data[3] * other.data[3]);
    }

    float Vector4D::Length() const
    {
        return sqrt((this->data[0] * this->data[0]) +
                    (this->data[1] * this->data[1]) +
                    (this->data[2] * this->data[2]) +
                    (this->data[3] * this->data[3]));
    }

    Vector4D Vector4D::Normalize() const
    {
        Vector4D vec;
        vec.data[0] = this->data[0] / this->Length();
        vec.data[1] = this->data[1] / this->Length();
        vec.data[2] = this->data[2] / this->Length();
        vec.data[3] = this->data[3] / this->Length();
        return vec;
    }

    float Vector4D::Distance(const Vector4D& other) const
    {
        return (*this - other).Length();
    }
}