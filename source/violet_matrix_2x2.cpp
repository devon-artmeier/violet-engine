#include "violet_engine_internal.hpp"

namespace Violet
{
	Matrix2x2::Matrix2x2(const float value)
    {
        this->data[0][0] = value;
        this->data[0][1] = value;
        this->data[1][0] = value;
        this->data[1][1] = value;
    }

    Matrix2x2::Matrix2x2(const float value1, const float value2,
                         const float value3, const float value4)
    {
        this->data[0][0] = value1;
        this->data[0][1] = value2;
        this->data[1][0] = value3;
        this->data[1][1] = value4;
    }

    Matrix2x2::Matrix2x2(const float arr[4])
    {
        this->data[0][0] = arr[0];
        this->data[0][1] = arr[1];
        this->data[1][0] = arr[2];
        this->data[1][1] = arr[3];
    }

    Matrix2x2::Matrix2x2(const Vector2& vec1, const Vector2& vec2)
    {
        this->data[0][0] = vec1[0];
        this->data[0][1] = vec1[1];
        this->data[1][0] = vec2[0];
        this->data[1][1] = vec2[1];
    }

    Matrix2x2::Matrix2x2(const Matrix2x2& mat)
    {
        this->data[0][0] = mat[0][0];
        this->data[0][1] = mat[0][1];
        this->data[1][0] = mat[1][0];
        this->data[1][1] = mat[1][1];
    }

    Matrix2x2& Matrix2x2::operator=(const Matrix2x2& mat)
    {
        this->data[0][0] = mat[0][0];
        this->data[0][1] = mat[0][1];
        this->data[1][0] = mat[1][0];
        this->data[1][1] = mat[1][1];
        return *this;
    }

    Matrix2x2 Matrix2x2::operator+(const Matrix2x2& mat) const
    {
        return Matrix2x2((this->data[0][0] + mat[0][0]),
                         (this->data[0][1] + mat[0][1]),
                         (this->data[1][0] + mat[1][0]),
                         (this->data[1][1] + mat[1][1]));
    }

    Matrix2x2 Matrix2x2::operator-(const Matrix2x2& mat) const
    {
        return Matrix2x2((this->data[0][0] - mat[0][0]),
                         (this->data[0][1] - mat[0][1]),
                         (this->data[1][0] - mat[1][0]),
                         (this->data[1][1] - mat[1][1]));
    }

    Vector2 Matrix2x2::operator*(const Vector2& vec) const
    {
        return Vector2((this->data[0][0] * vec[0]) + (this->data[1][0] * vec[1]),
                       (this->data[0][1] * vec[0]) + (this->data[1][1] * vec[1]));
    }

    Matrix2x2 Matrix2x2::operator*(const Matrix2x2& mat) const
    {
        return Matrix2x2((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]));
    }

    Matrix2x3 Matrix2x2::operator*(const Matrix2x3& mat) const
    {
        return Matrix2x3((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]),
                         (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]),
                         (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]));
    }

    Matrix2x4 Matrix2x2::operator*(const Matrix2x4& mat) const
    {
        return Matrix2x4((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]),
                         (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]),
                         (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]),
                         (this->data[0][0] * mat[3][0]) + (this->data[1][0] * mat[3][1]),
                         (this->data[0][1] * mat[3][0]) + (this->data[1][1] * mat[3][1]));
    }

    Matrix2x2 Matrix2x2::operator/(const Matrix2x2& mat) const
    {
        return Matrix2x2(this->data[0][0] / mat[0][0],
                         this->data[0][1] / mat[0][1],
                         this->data[1][0] / mat[1][0],
                         this->data[1][1] / mat[1][1]);
    }

    Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& mat)
    {
        this->data[0][0] += mat[0][0];
        this->data[0][1] += mat[0][1];
        this->data[1][0] += mat[1][0];
        this->data[1][1] += mat[1][1];
        return *this;
    }

    Matrix2x2& Matrix2x2::operator-=(const Matrix2x2& mat)
    {
        this->data[0][0] -= mat[0][0];
        this->data[0][1] -= mat[0][1];
        this->data[1][0] -= mat[1][0];
        this->data[1][1] -= mat[1][1];
        return *this;
    }

    Matrix2x2& Matrix2x2::operator*=(const Matrix2x2& mat)
    {
        this->data[0][0] = (this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]);
        this->data[0][1] = (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]);
        this->data[1][0] = (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]);
        this->data[1][1] = (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]);
        return *this;
    }

    Matrix2x2& Matrix2x2::operator/=(const Matrix2x2& mat)
    {
        this->data[0][0] /= mat[0][0];
        this->data[0][1] /= mat[0][1];
        this->data[1][0] /= mat[1][0];
        this->data[1][1] /= mat[1][1];
        return *this;
    }

    bool Matrix2x2::operator==(const Matrix2x2& mat)
    {
        return this->data[0][0] == mat[0][0] &&
               this->data[0][1] == mat[0][1] &&
               this->data[1][0] == mat[1][0] &&
               this->data[1][1] == mat[1][1];
    }

    float* Matrix2x2::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float* Matrix2x2::operator[](const size_t index) const
    {
        return this->data[index];
    }

    Matrix2x2 Matrix2x2::Identity()
    {
        return Matrix2x2(1, 0,
                         0, 1);
    }
}