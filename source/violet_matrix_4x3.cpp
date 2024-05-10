#include "violet_engine_internal.hpp"

namespace Violet
{
    Matrix4x3::Matrix4x3(const int value)
    {
        this->data[0][0] = static_cast<float>(value);
        this->data[0][1] = static_cast<float>(value);
        this->data[0][2] = static_cast<float>(value);
        this->data[0][3] = static_cast<float>(value);
        this->data[1][0] = static_cast<float>(value);
        this->data[1][1] = static_cast<float>(value);
        this->data[1][2] = static_cast<float>(value);
        this->data[1][3] = static_cast<float>(value);
        this->data[2][0] = static_cast<float>(value);
        this->data[2][1] = static_cast<float>(value);
        this->data[2][2] = static_cast<float>(value);
        this->data[2][3] = static_cast<float>(value);
    }

	Matrix4x3::Matrix4x3(const float value)
    {
        this->data[0][0] = value;
        this->data[0][1] = value;
        this->data[0][2] = value;
        this->data[0][3] = value;
        this->data[1][0] = value;
        this->data[1][1] = value;
        this->data[1][2] = value;
        this->data[1][3] = value;
        this->data[2][0] = value;
        this->data[2][1] = value;
        this->data[2][2] = value;
        this->data[2][3] = value;
    }

    Matrix4x3::Matrix4x3(const float value1,  const float value2,  const float value3,  const float value4,
                         const float value5,  const float value6,  const float value7,  const float value8,
                         const float value9,  const float value10, const float value11, const float value12)
    {
        this->data[0][0] = value1;
        this->data[0][1] = value2;
        this->data[0][2] = value3;
        this->data[0][3] = value4;
        this->data[1][0] = value5;
        this->data[1][1] = value6;
        this->data[1][2] = value7;
        this->data[1][3] = value8;
        this->data[2][0] = value9;
        this->data[2][1] = value10;
        this->data[2][2] = value11;
        this->data[2][3] = value12;
    }

    Matrix4x3::Matrix4x3(const float arr[12])
    {
        this->data[0][0] = arr[0];
        this->data[0][1] = arr[1];
        this->data[0][2] = arr[2];
        this->data[0][3] = arr[3];
        this->data[1][0] = arr[4];
        this->data[1][1] = arr[5];
        this->data[1][2] = arr[6];
        this->data[1][3] = arr[7];
        this->data[2][0] = arr[8];
        this->data[2][1] = arr[9];
        this->data[2][2] = arr[10];
        this->data[2][3] = arr[11];
    }

    Matrix4x3::Matrix4x3(const Vector4& vec1, const Vector4& vec2, const Vector4& vec3)
    {
        this->data[0][0] = vec1[0];
        this->data[0][1] = vec1[1];
        this->data[0][2] = vec1[2];
        this->data[0][3] = vec1[3];
        this->data[1][0] = vec2[0];
        this->data[1][1] = vec2[1];
        this->data[1][2] = vec2[2];
        this->data[1][3] = vec2[3];
        this->data[2][0] = vec3[0];
        this->data[2][1] = vec3[1];
        this->data[2][2] = vec3[2];
        this->data[2][3] = vec3[3];
    }

    Matrix4x3::Matrix4x3(const Matrix4x3& mat)
    {
        this->data[0][0] = mat[0][0];
        this->data[0][1] = mat[0][1];
        this->data[0][2] = mat[0][2];
        this->data[0][3] = mat[0][3];
        this->data[1][0] = mat[1][0];
        this->data[1][1] = mat[1][1];
        this->data[1][2] = mat[1][2];
        this->data[1][3] = mat[1][3];
        this->data[2][0] = mat[2][0];
        this->data[2][1] = mat[2][1];
        this->data[2][2] = mat[2][2];
        this->data[2][3] = mat[2][3];
    }

    Matrix4x3 Matrix4x3::operator+(const Matrix4x3& mat) const
    {
        return Matrix4x3((this->data[0][0] + mat[0][0]),
                         (this->data[0][1] + mat[0][1]),
                         (this->data[0][2] + mat[0][2]),
                         (this->data[0][3] + mat[0][3]),
                         (this->data[1][0] + mat[1][0]),
                         (this->data[1][1] + mat[1][1]),
                         (this->data[1][2] + mat[1][2]),
                         (this->data[1][3] + mat[1][3]),
                         (this->data[2][0] + mat[2][0]),
                         (this->data[2][1] + mat[2][1]),
                         (this->data[2][2] + mat[2][2]),
                         (this->data[2][3] + mat[2][3]));
    }

    Matrix4x3 Matrix4x3::operator-(const Matrix4x3& mat) const
    {
        return Matrix4x3((this->data[0][0] - mat[0][0]),
                         (this->data[0][1] - mat[0][1]),
                         (this->data[0][2] - mat[0][2]),
                         (this->data[0][3] - mat[0][3]),
                         (this->data[1][0] - mat[1][0]),
                         (this->data[1][1] - mat[1][1]),
                         (this->data[1][2] - mat[1][2]),
                         (this->data[1][3] - mat[1][3]),
                         (this->data[2][0] - mat[2][0]),
                         (this->data[2][1] - mat[2][1]),
                         (this->data[2][2] - mat[2][2]),
                         (this->data[2][3] - mat[2][3]));
    }

    Vector4 Matrix4x3::operator*(const Vector3& vec) const
    {
        return Vector4((this->data[0][0] * vec[0]) + (this->data[1][0] * vec[1]) + (this->data[2][0] * vec[2]),
                       (this->data[0][1] * vec[0]) + (this->data[1][1] * vec[1]) + (this->data[2][1] * vec[2]),
                       (this->data[0][2] * vec[0]) + (this->data[1][2] * vec[1]) + (this->data[2][2] * vec[2]),
                       (this->data[0][3] * vec[0]) + (this->data[1][3] * vec[1]) + (this->data[2][3] * vec[2]));
    }

    Matrix4x2 Matrix4x3::operator*(const Matrix3x2& mat) const
    {
        return Matrix4x2((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]),
                         (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]) + (this->data[2][2] * mat[0][2]),
                         (this->data[0][3] * mat[0][0]) + (this->data[1][3] * mat[0][1]) + (this->data[2][3] * mat[0][2]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]),
                         (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]) + (this->data[2][2] * mat[1][2]),
                         (this->data[0][3] * mat[1][0]) + (this->data[1][3] * mat[1][1]) + (this->data[2][3] * mat[1][2]));
    }

    Matrix4x3 Matrix4x3::operator*(const Matrix3x3& mat) const
    {
        return Matrix4x3((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]),
                         (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]) + (this->data[2][2] * mat[0][2]),
                         (this->data[0][3] * mat[0][0]) + (this->data[1][3] * mat[0][1]) + (this->data[2][3] * mat[0][2]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]),
                         (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]) + (this->data[2][2] * mat[1][2]),
                         (this->data[0][3] * mat[1][0]) + (this->data[1][3] * mat[1][1]) + (this->data[2][3] * mat[1][2]),
                         (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]) + (this->data[2][0] * mat[2][2]),
                         (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]) + (this->data[2][1] * mat[2][2]),
                         (this->data[0][2] * mat[2][0]) + (this->data[1][2] * mat[2][1]) + (this->data[2][2] * mat[2][2]),
                         (this->data[0][3] * mat[2][0]) + (this->data[1][3] * mat[2][1]) + (this->data[2][3] * mat[2][2]));
    }

    Matrix4x4 Matrix4x3::operator*(const Matrix3x4& mat) const
    {
        return Matrix4x4((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]),
                         (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]) + (this->data[2][2] * mat[0][2]),
                         (this->data[0][3] * mat[0][0]) + (this->data[1][3] * mat[0][1]) + (this->data[2][3] * mat[0][2]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]),
                         (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]) + (this->data[2][2] * mat[1][2]),
                         (this->data[0][3] * mat[1][0]) + (this->data[1][3] * mat[1][1]) + (this->data[2][3] * mat[1][2]),
                         (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]) + (this->data[2][0] * mat[2][2]),
                         (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]) + (this->data[2][1] * mat[2][2]),
                         (this->data[0][2] * mat[2][0]) + (this->data[1][2] * mat[2][1]) + (this->data[2][2] * mat[2][2]),
                         (this->data[0][3] * mat[2][0]) + (this->data[1][3] * mat[2][1]) + (this->data[2][3] * mat[2][2]),
                         (this->data[0][0] * mat[3][0]) + (this->data[1][0] * mat[3][1]) + (this->data[2][0] * mat[3][2]),
                         (this->data[0][1] * mat[3][0]) + (this->data[1][1] * mat[3][1]) + (this->data[2][1] * mat[3][2]),
                         (this->data[0][2] * mat[3][0]) + (this->data[1][2] * mat[3][1]) + (this->data[2][2] * mat[3][2]),
                         (this->data[0][3] * mat[3][0]) + (this->data[1][3] * mat[3][1]) + (this->data[2][3] * mat[3][2]));
    }

    Matrix4x3 Matrix4x3::operator/(const Matrix4x3& mat) const
    {
        return Matrix4x3(this->data[0][0] / mat[0][0],
                         this->data[0][1] / mat[0][1],
                         this->data[0][2] / mat[0][2],
                         this->data[0][3] / mat[0][3],
                         this->data[1][0] / mat[1][0],
                         this->data[1][1] / mat[1][1],
                         this->data[1][2] / mat[1][2],
                         this->data[1][3] / mat[1][3],
                         this->data[2][0] / mat[2][0],
                         this->data[2][1] / mat[2][1],
                         this->data[2][2] / mat[2][2],
                         this->data[2][3] / mat[2][3]);
    }

    Matrix4x3& Matrix4x3::operator+=(const Matrix4x3& mat)
    {
        this->data[0][0] += mat[0][0];
        this->data[0][1] += mat[0][1];
        this->data[0][2] += mat[0][2];
        this->data[0][3] += mat[0][3];
        this->data[1][0] += mat[1][0];
        this->data[1][1] += mat[1][1];
        this->data[1][2] += mat[1][2];
        this->data[1][3] += mat[1][3];
        this->data[2][0] += mat[2][0];
        this->data[2][1] += mat[2][1];
        this->data[2][2] += mat[2][2];
        this->data[2][3] += mat[2][3];
        return *this;
    }

    Matrix4x3& Matrix4x3::operator-=(const Matrix4x3& mat)
    {
        this->data[0][0] -= mat[0][0];
        this->data[0][1] -= mat[0][1];
        this->data[0][2] -= mat[0][2];
        this->data[0][3] -= mat[0][3];
        this->data[1][0] -= mat[1][0];
        this->data[1][1] -= mat[1][1];
        this->data[1][2] -= mat[1][2];
        this->data[1][3] -= mat[1][3];
        this->data[2][0] -= mat[2][0];
        this->data[2][1] -= mat[2][1];
        this->data[2][2] -= mat[2][2];
        this->data[2][3] -= mat[2][3];
        return *this;
    }

    Matrix4x3& Matrix4x3::operator*=(const Matrix3x3& mat)
    {
        this->data[0][0] = (this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]);
        this->data[0][1] = (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]);
        this->data[0][2] = (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]) + (this->data[2][2] * mat[0][2]);
        this->data[0][3] = (this->data[0][3] * mat[0][0]) + (this->data[1][3] * mat[0][1]) + (this->data[2][3] * mat[0][2]);
        this->data[1][0] = (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]);
        this->data[1][1] = (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]);
        this->data[1][2] = (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]) + (this->data[2][2] * mat[1][2]);
        this->data[1][3] = (this->data[0][3] * mat[1][0]) + (this->data[1][3] * mat[1][1]) + (this->data[2][3] * mat[1][2]);
        this->data[2][0] = (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]) + (this->data[2][0] * mat[2][2]);
        this->data[2][1] = (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]) + (this->data[2][1] * mat[2][2]);
        this->data[2][2] = (this->data[0][2] * mat[2][0]) + (this->data[1][2] * mat[2][1]) + (this->data[2][2] * mat[2][2]);
        this->data[2][3] = (this->data[0][3] * mat[2][0]) + (this->data[1][3] * mat[2][1]) + (this->data[2][3] * mat[2][2]);
        return *this;
    }

    Matrix4x3& Matrix4x3::operator/=(const Matrix4x3& mat)
    {
        this->data[0][0] /= mat[0][0];
        this->data[0][1] /= mat[0][1];
        this->data[0][2] /= mat[0][2];
        this->data[0][2] /= mat[0][2];
        this->data[1][0] /= mat[1][0];
        this->data[1][1] /= mat[1][1];
        this->data[1][2] /= mat[1][2];
        this->data[1][3] /= mat[1][3];
        this->data[2][0] /= mat[2][0];
        this->data[2][1] /= mat[2][1];
        this->data[2][2] /= mat[2][2];
        this->data[2][3] /= mat[2][3];
        return *this;
    }

    bool Matrix4x3::operator==(const Matrix4x3& mat)
    {
        return this->data[0][0] == mat[0][0] &&
               this->data[0][1] == mat[0][1] &&
               this->data[0][2] == mat[0][2] &&
               this->data[0][3] == mat[0][3] &&
               this->data[1][0] == mat[1][0] &&
               this->data[1][1] == mat[1][1] &&
               this->data[1][2] == mat[1][2] &&
               this->data[1][3] == mat[1][3] &&
               this->data[2][0] == mat[2][0] &&
               this->data[2][1] == mat[2][1] &&
               this->data[2][2] == mat[2][2] &&
               this->data[2][3] == mat[2][3];
    }

    float* Matrix4x3::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float* Matrix4x3::operator[](const size_t index) const
    {
        return this->data[index];
    }
}