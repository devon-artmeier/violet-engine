#include "violet_engine_internal.hpp"

namespace Violet
{
	Matrix3x2::Matrix3x2(const float value)
    {
        this->data[0][0] = value;
        this->data[0][1] = value;
        this->data[0][2] = value;
        this->data[1][0] = value;
        this->data[1][1] = value;
        this->data[1][2] = value;
    }

    Matrix3x2::Matrix3x2(const float value1, const float value2, const float value3,
                         const float value4, const float value5, const float value6)
    {
        this->data[0][0] = value1;
        this->data[0][1] = value2;
        this->data[0][2] = value3;
        this->data[1][0] = value4;
        this->data[1][1] = value5;
        this->data[1][2] = value6;
    }

    Matrix3x2::Matrix3x2(const float arr[6])
    {
        this->data[0][0] = arr[0];
        this->data[0][1] = arr[1];
        this->data[0][2] = arr[2];
        this->data[1][0] = arr[3];
        this->data[1][1] = arr[4];
        this->data[1][2] = arr[5];
    }

    Matrix3x2::Matrix3x2(const float arr1[3], const float arr2[3])
    {
        this->data[0][0] = arr1[0];
        this->data[0][1] = arr1[1];
        this->data[0][2] = arr1[2];
        this->data[1][0] = arr2[0];
        this->data[1][1] = arr2[1];
        this->data[1][2] = arr2[2];
    }

    Matrix3x2::Matrix3x2(const Vector3& vec1, const Vector3& vec2)
    {
        this->data[0][0] = vec1[0];
        this->data[0][1] = vec1[1];
        this->data[0][2] = vec1[2];
        this->data[1][0] = vec2[0];
        this->data[1][1] = vec2[1];
        this->data[1][2] = vec2[2];
    }

    Matrix3x2::Matrix3x2(const Matrix3x2& mat)
    {
        this->data[0][0] = mat[0][0];
        this->data[0][1] = mat[0][1];
        this->data[0][2] = mat[0][2];
        this->data[1][0] = mat[1][0];
        this->data[1][1] = mat[1][1];
        this->data[1][2] = mat[1][2];
    }

    Matrix3x2& Matrix3x2::operator=(const float value)
    {
        this->data[0][0] = value;
        this->data[0][1] = value;
        this->data[0][2] = value;
        this->data[1][0] = value;
        this->data[1][1] = value;
        this->data[1][2] = value;
        return *this;
    }

    Matrix3x2& Matrix3x2::operator=(const Matrix3x2& mat)
    {
        this->data[0][0] = mat[0][0];
        this->data[0][1] = mat[0][1];
        this->data[0][2] = mat[0][2];
        this->data[1][0] = mat[1][0];
        this->data[1][1] = mat[1][1];
        this->data[1][2] = mat[1][2];
        return *this;
    }

    Matrix3x2 Matrix3x2::operator+(const Matrix3x2& mat) const
    {
        return Matrix3x2((this->data[0][0] + mat[0][0]),
                         (this->data[0][1] + mat[0][1]),
                         (this->data[0][2] + mat[0][2]),
                         (this->data[1][0] + mat[1][0]),
                         (this->data[1][1] + mat[1][1]),
                         (this->data[1][2] + mat[1][2]));
    }

    Matrix3x2 Matrix3x2::operator-(const Matrix3x2& mat) const
    {
        return Matrix3x2((this->data[0][0] - mat[0][0]),
                         (this->data[0][1] - mat[0][1]),
                         (this->data[0][2] - mat[0][2]),
                         (this->data[1][0] - mat[1][0]),
                         (this->data[1][1] - mat[1][1]),
                         (this->data[1][2] - mat[1][2]));
    }

    Vector3 Matrix3x2::operator*(const Vector2& vec) const
    {
        return Vector3((this->data[0][0] * vec[0]) + (this->data[1][0] * vec[1]),
                       (this->data[0][1] * vec[0]) + (this->data[1][1] * vec[1]),
                       (this->data[0][2] * vec[0]) + (this->data[1][2] * vec[1]));
    }

    Matrix3x2 Matrix3x2::operator*(const Matrix2x2& mat) const
    {
        return Matrix3x2((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]),
                         (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]),
                         (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]));
    }

    Matrix3x3 Matrix3x2::operator*(const Matrix2x3& mat) const
    {
        return Matrix3x3((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]),
                         (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]),
                         (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]),
                         (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]),
                         (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]),
                         (this->data[0][2] * mat[2][0]) + (this->data[1][2] * mat[2][1]));
    }

    Matrix3x4 Matrix3x2::operator*(const Matrix2x4& mat) const
    {
        return Matrix3x4((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]),
                         (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]),
                         (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]),
                         (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]),
                         (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]),
                         (this->data[0][2] * mat[2][0]) + (this->data[1][2] * mat[2][1]),
                         (this->data[0][0] * mat[3][0]) + (this->data[1][0] * mat[3][1]),
                         (this->data[0][1] * mat[3][0]) + (this->data[1][1] * mat[3][1]),
                         (this->data[0][2] * mat[3][0]) + (this->data[1][2] * mat[3][1]));
    }

    Matrix3x2& Matrix3x2::operator+=(const Matrix3x2& mat)
    {
        this->data[0][0] += mat[0][0];
        this->data[0][1] += mat[0][1];
        this->data[0][2] += mat[0][2];
        this->data[1][0] += mat[1][0];
        this->data[1][1] += mat[1][1];
        this->data[1][2] += mat[1][2];
        return *this;
    }

    Matrix3x2& Matrix3x2::operator-=(const Matrix3x2& mat)
    {
        this->data[0][0] -= mat[0][0];
        this->data[0][1] -= mat[0][1];
        this->data[0][2] -= mat[0][2];
        this->data[1][0] -= mat[1][0];
        this->data[1][1] -= mat[1][1];
        this->data[1][2] -= mat[1][2];
        return *this;
    }

    Matrix3x2& Matrix3x2::operator*=(const Matrix2x2& mat)
    {
        this->data[0][0] = (this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]);
        this->data[0][1] = (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]);
        this->data[0][2] = (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]);
        this->data[1][0] = (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]);
        this->data[1][1] = (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]);
        this->data[1][2] = (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]);
        return *this;
    }

    float* Matrix3x2::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float* Matrix3x2::operator[](const size_t index) const
    {
        return this->data[index];
    }
}