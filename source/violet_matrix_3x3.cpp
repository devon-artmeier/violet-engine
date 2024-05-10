#include "violet_engine_internal.hpp"

namespace Violet
{
	Matrix3x3::Matrix3x3(const float value)
    {
        this->data[0][0] = value;
        this->data[0][1] = value;
        this->data[0][2] = value;
        this->data[1][0] = value;
        this->data[1][1] = value;
        this->data[1][2] = value;
        this->data[2][0] = value;
        this->data[2][1] = value;
        this->data[2][2] = value;
    }

    Matrix3x3::Matrix3x3(const float value1, const float value2, const float value3,
                         const float value4, const float value5, const float value6,
                         const float value7, const float value8, const float value9)
    {
        this->data[0][0] = value1;
        this->data[0][1] = value2;
        this->data[0][2] = value3;
        this->data[1][0] = value4;
        this->data[1][1] = value5;
        this->data[1][2] = value6;
        this->data[2][0] = value7;
        this->data[2][1] = value8;
        this->data[2][2] = value9;
    }

    Matrix3x3::Matrix3x3(const float arr[9])
    {
        this->data[0][0] = arr[0];
        this->data[0][1] = arr[1];
        this->data[0][2] = arr[2];
        this->data[1][0] = arr[3];
        this->data[1][1] = arr[4];
        this->data[1][2] = arr[5];
        this->data[2][0] = arr[6];
        this->data[2][1] = arr[7];
        this->data[2][2] = arr[8];
    }

    Matrix3x3::Matrix3x3(const float arr1[3], const float arr2[3], const float arr3[3])
    {
        this->data[0][0] = arr1[0];
        this->data[0][1] = arr1[1];
        this->data[0][2] = arr1[2];
        this->data[1][0] = arr2[0];
        this->data[1][1] = arr2[1];
        this->data[1][2] = arr2[2];
        this->data[2][0] = arr3[0];
        this->data[2][1] = arr3[1];
        this->data[2][2] = arr3[2];
    }

    Matrix3x3::Matrix3x3(const Vector3& vec1, const Vector3& vec2, const Vector3& vec3)
    {
        this->data[0][0] = vec1[0];
        this->data[0][1] = vec1[1];
        this->data[0][2] = vec1[2];
        this->data[1][0] = vec2[0];
        this->data[1][1] = vec2[1];
        this->data[1][2] = vec2[2];
        this->data[2][0] = vec3[0];
        this->data[2][1] = vec3[1];
        this->data[2][2] = vec3[2];
    }

    Matrix3x3::Matrix3x3(const Matrix3x3& mat)
    {
        this->data[0][0] = mat[0][0];
        this->data[0][1] = mat[0][1];
        this->data[0][2] = mat[0][2];
        this->data[1][0] = mat[1][0];
        this->data[1][1] = mat[1][1];
        this->data[1][2] = mat[1][2];
        this->data[2][0] = mat[2][0];
        this->data[2][1] = mat[2][1];
        this->data[2][2] = mat[2][2];
    }

    Matrix3x3& Matrix3x3::operator=(const float value)
    {
        this->data[0][0] = value;
        this->data[0][1] = value;
        this->data[0][2] = value;
        this->data[1][0] = value;
        this->data[1][1] = value;
        this->data[1][2] = value;
        this->data[2][0] = value;
        this->data[2][1] = value;
        this->data[2][2] = value;
        return *this;
    }

    Matrix3x3& Matrix3x3::operator=(const Matrix3x3& mat)
    {
        this->data[0][0] = mat[0][0];
        this->data[0][1] = mat[0][1];
        this->data[0][2] = mat[0][2];
        this->data[1][0] = mat[1][0];
        this->data[1][1] = mat[1][1];
        this->data[1][2] = mat[1][2];
        this->data[2][0] = mat[2][0];
        this->data[2][1] = mat[2][1];
        this->data[2][2] = mat[2][2];
        return *this;
    }

    Matrix3x3 Matrix3x3::operator+(const Matrix3x3& mat) const
    {
        return Matrix3x3((this->data[0][0] + mat[0][0]),
                         (this->data[0][1] + mat[0][1]),
                         (this->data[0][2] + mat[0][2]),
                         (this->data[1][0] + mat[1][0]),
                         (this->data[1][1] + mat[1][1]),
                         (this->data[1][2] + mat[1][2]),
                         (this->data[2][0] + mat[2][0]),
                         (this->data[2][1] + mat[2][1]),
                         (this->data[2][2] + mat[2][2]));
    }

    Matrix3x3 Matrix3x3::operator-(const Matrix3x3& mat) const
    {
        return Matrix3x3((this->data[0][0] - mat[0][0]),
                         (this->data[0][1] - mat[0][1]),
                         (this->data[0][2] - mat[0][2]),
                         (this->data[1][0] - mat[1][0]),
                         (this->data[1][1] - mat[1][1]),
                         (this->data[1][2] - mat[1][2]),
                         (this->data[2][0] - mat[2][0]),
                         (this->data[2][1] - mat[2][1]),
                         (this->data[2][2] - mat[2][2]));
    }

    Vector3 Matrix3x3::operator*(const Vector3& vec) const
    {
        return Vector3((this->data[0][0] * vec[0]) + (this->data[1][0] * vec[1]) + (this->data[2][0] * vec[2]),
                       (this->data[0][1] * vec[0]) + (this->data[1][1] * vec[1]) + (this->data[2][1] * vec[2]),
                       (this->data[0][2] * vec[0]) + (this->data[1][2] * vec[1]) + (this->data[2][2] * vec[2]));
    }

    Matrix3x2 Matrix3x3::operator*(const Matrix3x2& mat) const
    {
        return Matrix3x2((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]),
                         (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]) + (this->data[2][2] * mat[0][2]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]),
                         (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]) + (this->data[2][2] * mat[1][2]));
    }

    Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mat) const
    {
        return Matrix3x3((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]),
                         (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]) + (this->data[2][2] * mat[0][2]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]),
                         (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]) + (this->data[2][2] * mat[1][2]),
                         (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]) + (this->data[2][0] * mat[2][2]),
                         (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]) + (this->data[2][1] * mat[2][2]),
                         (this->data[0][2] * mat[2][0]) + (this->data[1][2] * mat[2][1]) + (this->data[2][2] * mat[2][2]));
    }

    Matrix3x4 Matrix3x3::operator*(const Matrix3x4& mat) const
    {
        return Matrix3x4((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]),
                         (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]) + (this->data[2][2] * mat[0][2]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]),
                         (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]) + (this->data[2][2] * mat[1][2]),
                         (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]) + (this->data[2][0] * mat[2][2]),
                         (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]) + (this->data[2][1] * mat[2][2]),
                         (this->data[0][2] * mat[2][0]) + (this->data[1][2] * mat[2][1]) + (this->data[2][2] * mat[2][2]),
                         (this->data[0][0] * mat[3][0]) + (this->data[1][0] * mat[3][1]) + (this->data[2][0] * mat[3][2]),
                         (this->data[0][1] * mat[3][0]) + (this->data[1][1] * mat[3][1]) + (this->data[2][1] * mat[3][2]),
                         (this->data[0][2] * mat[3][0]) + (this->data[1][2] * mat[3][1]) + (this->data[2][2] * mat[3][2]));
    }

    Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& mat)
    {
        this->data[0][0] += mat[0][0];
        this->data[0][1] += mat[0][1];
        this->data[0][2] += mat[0][2];
        this->data[1][0] += mat[1][0];
        this->data[1][1] += mat[1][1];
        this->data[1][2] += mat[1][2];
        this->data[2][0] += mat[2][0];
        this->data[2][1] += mat[2][1];
        this->data[2][2] += mat[2][2];
        return *this;
    }

    Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& mat)
    {
        this->data[0][0] -= mat[0][0];
        this->data[0][1] -= mat[0][1];
        this->data[0][2] -= mat[0][2];
        this->data[1][0] -= mat[1][0];
        this->data[1][1] -= mat[1][1];
        this->data[1][2] -= mat[1][2];
        this->data[2][0] -= mat[2][0];
        this->data[2][1] -= mat[2][1];
        this->data[2][2] -= mat[2][2];
        return *this;
    }

    Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& mat)
    {
        this->data[0][0] = (this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]);
        this->data[0][1] = (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]);
        this->data[0][2] = (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]) + (this->data[2][2] * mat[0][2]);
        this->data[1][0] = (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]);
        this->data[1][1] = (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]);
        this->data[1][2] = (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]) + (this->data[2][2] * mat[1][2]);
        this->data[2][0] = (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]) + (this->data[2][0] * mat[2][2]);
        this->data[2][1] = (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]) + (this->data[2][1] * mat[2][2]);
        this->data[2][2] = (this->data[0][2] * mat[2][0]) + (this->data[1][2] * mat[2][1]) + (this->data[2][2] * mat[2][2]);
        return *this;
    }

    float* Matrix3x3::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float* Matrix3x3::operator[](const size_t index) const
    {
        return this->data[index];
    }

    Matrix3x3 Matrix3x3::Identity()
    {
        return Matrix3x3(1, 0, 0,
                         0, 1, 0,
                         0, 0, 1);
    }
}