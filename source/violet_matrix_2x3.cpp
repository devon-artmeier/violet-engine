#include "violet_engine_internal.hpp"

namespace Violet
{
	Matrix2x3::Matrix2x3(const float value)
    {
        this->data[0][0] = value;
        this->data[0][1] = value;
        this->data[1][0] = value;
        this->data[1][1] = value;
        this->data[2][0] = value;
        this->data[2][1] = value;
    }

    Matrix2x3::Matrix2x3(const float value1, const float value2,
                         const float value3, const float value4,
                         const float value5, const float value6)
    {
        this->data[0][0] = value1;
        this->data[0][1] = value2;
        this->data[1][0] = value3;
        this->data[1][1] = value4;
        this->data[2][0] = value5;
        this->data[2][1] = value6;
    }

    Matrix2x3::Matrix2x3(const float arr[6])
    {
        this->data[0][0] = arr[0];
        this->data[0][1] = arr[1];
        this->data[1][0] = arr[2];
        this->data[1][1] = arr[3];
        this->data[2][0] = arr[4];
        this->data[2][1] = arr[5];
    }

    Matrix2x3::Matrix2x3(const float arr1[2], const float arr2[2], const float arr3[2])
    {
        this->data[0][0] = arr1[0];
        this->data[0][1] = arr1[1];
        this->data[1][0] = arr2[0];
        this->data[1][1] = arr2[1];
        this->data[2][0] = arr3[0];
        this->data[2][1] = arr3[1];
    }

    Matrix2x3::Matrix2x3(const Vector2& vec1, const Vector2& vec2, const Vector2& vec3)
    {
        this->data[0][0] = vec1[0];
        this->data[0][1] = vec1[1];
        this->data[1][0] = vec2[0];
        this->data[1][1] = vec2[1];
        this->data[2][0] = vec3[0];
        this->data[2][1] = vec3[1];
    }

    Matrix2x3::Matrix2x3(const Matrix2x3& mat)
    {
        this->data[0][0] = mat[0][0];
        this->data[0][1] = mat[0][1];
        this->data[1][0] = mat[1][0];
        this->data[1][1] = mat[1][1];
        this->data[2][0] = mat[2][0];
        this->data[2][1] = mat[2][1];
    }

    Matrix2x3& Matrix2x3::operator=(const float value)
    {
        this->data[0][0] = value;
        this->data[0][1] = value;
        this->data[1][0] = value;
        this->data[1][1] = value;
        this->data[2][0] = value;
        this->data[2][1] = value;
        return *this;
    }

    Matrix2x3& Matrix2x3::operator=(const Matrix2x3& mat)
    {
        this->data[0][0] = mat[0][0];
        this->data[0][1] = mat[0][1];
        this->data[1][0] = mat[1][0];
        this->data[1][1] = mat[1][1];
        this->data[2][0] = mat[2][0];
        this->data[2][1] = mat[2][1];
        return *this;
    }

    Matrix2x3 Matrix2x3::operator+(const Matrix2x3& mat) const
    {
        return Matrix2x3((this->data[0][0] + mat[0][0]),
                         (this->data[0][1] + mat[0][1]),
                         (this->data[1][0] + mat[1][0]),
                         (this->data[1][1] + mat[1][1]),
                         (this->data[2][0] + mat[2][0]),
                         (this->data[2][1] + mat[2][1]));
    }

    Matrix2x3 Matrix2x3::operator-(const Matrix2x3& mat) const
    {
        return Matrix2x3((this->data[0][0] - mat[0][0]),
                         (this->data[0][1] - mat[0][1]),
                         (this->data[1][0] - mat[1][0]),
                         (this->data[1][1] - mat[1][1]),
                         (this->data[2][0] - mat[2][0]),
                         (this->data[2][1] - mat[2][1]));
    }

    Vector2 Matrix2x3::operator*(const Vector3& vec) const
    {
        return Vector2((this->data[0][0] * vec[0]) + (this->data[1][0] * vec[1]) + (this->data[2][0] * vec[2]),
                       (this->data[0][1] * vec[0]) + (this->data[1][1] * vec[1]) + (this->data[2][1] * vec[2]));
    }

    Matrix2x2 Matrix2x3::operator*(const Matrix3x2& mat) const
    {
        return Matrix2x2((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]));
    }

    Matrix2x3 Matrix2x3::operator*(const Matrix3x3& mat) const
    {
        return Matrix2x3((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]),
                         (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]) + (this->data[2][0] * mat[2][2]),
                         (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]) + (this->data[2][1] * mat[2][2]));
    }

    Matrix2x3& Matrix2x3::operator+=(const Matrix2x3& mat)
    {
        this->data[0][0] += mat[0][0];
        this->data[0][1] += mat[0][1];
        this->data[1][0] += mat[1][0];
        this->data[1][1] += mat[1][1];
        this->data[2][0] += mat[2][0];
        this->data[2][1] += mat[2][1];
        return *this;
    }

    Matrix2x3& Matrix2x3::operator-=(const Matrix2x3& mat)
    {
        this->data[0][0] -= mat[0][0];
        this->data[0][1] -= mat[0][1];
        this->data[1][0] -= mat[1][0];
        this->data[1][1] -= mat[1][1];
        this->data[2][0] -= mat[2][0];
        this->data[2][1] -= mat[2][1];
        return *this;
    }

    Matrix2x3& Matrix2x3::operator*=(const Matrix3x3& mat)
    {
        this->data[0][0] = (this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]);
        this->data[0][1] = (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]);
        this->data[1][0] = (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]);
        this->data[1][1] = (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]);
        this->data[2][0] = (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]) + (this->data[2][0] * mat[2][2]);
        this->data[2][1] = (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]) + (this->data[2][1] * mat[2][2]);
        return *this;
    }

    float* Matrix2x3::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float* Matrix2x3::operator[](const size_t index) const
    {
        return this->data[index];
    }
}