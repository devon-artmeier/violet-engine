#include "violet_engine_internal.hpp"

namespace Violet
{
	Matrix4x4::Matrix4x4(const float value)
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
        this->data[3][0] = value;
        this->data[3][1] = value;
        this->data[3][2] = value;
        this->data[3][3] = value;
    }

    Matrix4x4::Matrix4x4(const float value1,  const float value2,  const float value3,  const float value4,
                         const float value5,  const float value6,  const float value7,  const float value8,
                         const float value9,  const float value10, const float value11, const float value12,
                         const float value13, const float value14, const float value15, const float value16)
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
        this->data[3][0] = value13;
        this->data[3][1] = value14;
        this->data[3][2] = value15;
        this->data[3][3] = value16;
    }

    Matrix4x4::Matrix4x4(const float arr[16])
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
        this->data[3][0] = arr[12];
        this->data[3][1] = arr[13];
        this->data[3][2] = arr[14];
        this->data[3][3] = arr[15];
    }

    Matrix4x4::Matrix4x4(const float arr1[4], const float arr2[4], const float arr3[4], const float arr4[4])
    {
        this->data[0][0] = arr1[0];
        this->data[0][1] = arr1[1];
        this->data[0][2] = arr1[2];
        this->data[0][3] = arr1[3];
        this->data[1][0] = arr2[0];
        this->data[1][1] = arr2[1];
        this->data[1][2] = arr2[2];
        this->data[1][3] = arr2[3];
        this->data[2][0] = arr3[0];
        this->data[2][1] = arr3[1];
        this->data[2][2] = arr3[2];
        this->data[2][3] = arr3[3];
        this->data[3][0] = arr4[0];
        this->data[3][1] = arr4[1];
        this->data[3][2] = arr4[2];
        this->data[3][3] = arr4[3];
    }

    Matrix4x4::Matrix4x4(const Vector4& vec1, const Vector4& vec2, const Vector4& vec3, const Vector4& vec4)
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
        this->data[3][0] = vec4[0];
        this->data[3][1] = vec4[1];
        this->data[3][2] = vec4[2];
        this->data[3][3] = vec4[3];
    }

    Matrix4x4::Matrix4x4(const Matrix4x4& mat)
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
        this->data[3][0] = mat[3][0];
        this->data[3][1] = mat[3][1];
        this->data[3][2] = mat[3][2];
        this->data[3][3] = mat[3][3];
    }

    Matrix4x4& Matrix4x4::operator=(const float value)
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
        this->data[3][0] = value;
        this->data[3][1] = value;
        this->data[3][2] = value;
        this->data[3][3] = value;
        return *this;
    }

    Matrix4x4& Matrix4x4::operator=(const Matrix4x4& mat)
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
        this->data[3][0] = mat[3][0];
        this->data[3][1] = mat[3][1];
        this->data[3][2] = mat[3][2];
        this->data[3][3] = mat[3][3];
        return *this;
    }

    Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mat) const
    {
        return Matrix4x4((this->data[0][0] + mat[0][0]),
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
                         (this->data[2][3] + mat[2][3]),
                         (this->data[3][0] + mat[3][0]),
                         (this->data[3][1] + mat[3][1]),
                         (this->data[3][2] + mat[3][2]),
                         (this->data[3][3] + mat[3][3]));
    }

    Matrix4x4 Matrix4x4::operator-(const Matrix4x4& mat) const
    {
        return Matrix4x4((this->data[0][0] - mat[0][0]),
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
                         (this->data[2][3] - mat[2][3]),
                         (this->data[3][0] - mat[3][0]),
                         (this->data[3][1] - mat[3][1]),
                         (this->data[3][2] - mat[3][2]),
                         (this->data[3][3] - mat[3][3]));
    }

    Vector4 Matrix4x4::operator*(const Vector4& vec) const
    {
        return Vector4((this->data[0][0] * vec[0]) + (this->data[1][0] * vec[1]) + (this->data[2][0] * vec[2]) + (this->data[3][0] * vec[3]),
                       (this->data[0][1] * vec[0]) + (this->data[1][1] * vec[1]) + (this->data[2][1] * vec[2]) + (this->data[3][1] * vec[3]),
                       (this->data[0][2] * vec[0]) + (this->data[1][2] * vec[1]) + (this->data[2][2] * vec[2]) + (this->data[3][2] * vec[3]),
                       (this->data[0][3] * vec[0]) + (this->data[1][3] * vec[1]) + (this->data[2][3] * vec[2]) + (this->data[3][3] * vec[3]));
    }

    Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const
    {
        return Matrix4x4((this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]) + (this->data[3][0] * mat[0][3]),
                         (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]) + (this->data[3][1] * mat[0][3]),
                         (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]) + (this->data[2][2] * mat[0][2]) + (this->data[3][2] * mat[0][3]),
                         (this->data[0][3] * mat[0][0]) + (this->data[1][3] * mat[0][1]) + (this->data[2][3] * mat[0][2]) + (this->data[3][3] * mat[0][3]),
                         (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]) + (this->data[3][0] * mat[1][3]),
                         (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]) + (this->data[3][1] * mat[1][3]),
                         (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]) + (this->data[2][2] * mat[1][2]) + (this->data[3][2] * mat[1][3]),
                         (this->data[0][3] * mat[1][0]) + (this->data[1][3] * mat[1][1]) + (this->data[2][3] * mat[1][2]) + (this->data[3][3] * mat[1][3]),
                         (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]) + (this->data[2][0] * mat[2][2]) + (this->data[3][0] * mat[2][3]),
                         (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]) + (this->data[2][1] * mat[2][2]) + (this->data[3][1] * mat[2][3]),
                         (this->data[0][2] * mat[2][0]) + (this->data[1][2] * mat[2][1]) + (this->data[2][2] * mat[2][2]) + (this->data[3][2] * mat[2][3]),
                         (this->data[0][3] * mat[2][0]) + (this->data[1][3] * mat[2][1]) + (this->data[2][3] * mat[2][2]) + (this->data[3][3] * mat[2][3]),
                         (this->data[0][0] * mat[3][0]) + (this->data[1][0] * mat[3][1]) + (this->data[2][0] * mat[3][2]) + (this->data[3][0] * mat[3][3]),
                         (this->data[0][1] * mat[3][0]) + (this->data[1][1] * mat[3][1]) + (this->data[2][1] * mat[3][2]) + (this->data[3][1] * mat[3][3]),
                         (this->data[0][2] * mat[3][0]) + (this->data[1][2] * mat[3][1]) + (this->data[2][2] * mat[3][2]) + (this->data[3][2] * mat[3][3]),
                         (this->data[0][3] * mat[3][0]) + (this->data[1][3] * mat[3][1]) + (this->data[2][3] * mat[3][2]) + (this->data[3][3] * mat[3][3]));
    }

    Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& mat)
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
        this->data[3][0] += mat[3][0];
        this->data[3][1] += mat[3][1];
        this->data[3][2] += mat[3][2];
        this->data[3][3] += mat[3][3];
        return *this;
    }

    Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& mat)
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
        this->data[3][0] -= mat[3][0];
        this->data[3][1] -= mat[3][1];
        this->data[3][2] -= mat[3][2];
        this->data[3][3] -= mat[3][3];
        return *this;
    }

    Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& mat)
    {
        this->data[0][0] = (this->data[0][0] * mat[0][0]) + (this->data[1][0] * mat[0][1]) + (this->data[2][0] * mat[0][2]) + (this->data[3][0] * mat[0][3]);
        this->data[0][1] = (this->data[0][1] * mat[0][0]) + (this->data[1][1] * mat[0][1]) + (this->data[2][1] * mat[0][2]) + (this->data[3][1] * mat[0][3]);
        this->data[0][2] = (this->data[0][2] * mat[0][0]) + (this->data[1][2] * mat[0][1]) + (this->data[2][2] * mat[0][2]) + (this->data[3][2] * mat[0][3]);
        this->data[0][3] = (this->data[0][3] * mat[0][0]) + (this->data[1][3] * mat[0][1]) + (this->data[2][3] * mat[0][2]) + (this->data[3][3] * mat[0][3]);
        this->data[1][0] = (this->data[0][0] * mat[1][0]) + (this->data[1][0] * mat[1][1]) + (this->data[2][0] * mat[1][2]) + (this->data[3][0] * mat[1][3]);
        this->data[1][1] = (this->data[0][1] * mat[1][0]) + (this->data[1][1] * mat[1][1]) + (this->data[2][1] * mat[1][2]) + (this->data[3][1] * mat[1][3]);
        this->data[1][2] = (this->data[0][2] * mat[1][0]) + (this->data[1][2] * mat[1][1]) + (this->data[2][2] * mat[1][2]) + (this->data[3][2] * mat[1][3]);
        this->data[1][3] = (this->data[0][3] * mat[1][0]) + (this->data[1][3] * mat[1][1]) + (this->data[2][3] * mat[1][2]) + (this->data[3][3] * mat[1][3]);
        this->data[2][0] = (this->data[0][0] * mat[2][0]) + (this->data[1][0] * mat[2][1]) + (this->data[2][0] * mat[2][2]) + (this->data[3][0] * mat[2][3]);
        this->data[2][1] = (this->data[0][1] * mat[2][0]) + (this->data[1][1] * mat[2][1]) + (this->data[2][1] * mat[2][2]) + (this->data[3][1] * mat[2][3]);
        this->data[2][2] = (this->data[0][2] * mat[2][0]) + (this->data[1][2] * mat[2][1]) + (this->data[2][2] * mat[2][2]) + (this->data[3][2] * mat[2][3]);
        this->data[2][3] = (this->data[0][3] * mat[2][0]) + (this->data[1][3] * mat[2][1]) + (this->data[2][3] * mat[2][2]) + (this->data[3][3] * mat[2][3]);
        this->data[3][0] = (this->data[0][0] * mat[3][0]) + (this->data[1][0] * mat[3][1]) + (this->data[2][0] * mat[3][2]) + (this->data[3][0] * mat[3][3]);
        this->data[3][1] = (this->data[0][1] * mat[3][0]) + (this->data[1][1] * mat[3][1]) + (this->data[2][1] * mat[3][2]) + (this->data[3][1] * mat[3][3]);
        this->data[3][2] = (this->data[0][2] * mat[3][0]) + (this->data[1][2] * mat[3][1]) + (this->data[2][2] * mat[3][2]) + (this->data[3][2] * mat[3][3]);
        this->data[3][3] = (this->data[0][3] * mat[3][0]) + (this->data[1][3] * mat[3][1]) + (this->data[2][3] * mat[3][2]) + (this->data[3][3] * mat[3][3]);
        return *this;
    }

    float* Matrix4x4::operator[](const size_t index)
    {
        return this->data[index];
    }

    const float* Matrix4x4::operator[](const size_t index) const
    {
        return this->data[index];
    }

    Matrix4x4 Matrix4x4::Identity()
    {
        return Matrix4x4(1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         0, 0, 0, 1);
    }

    Matrix4x4 OrthoMatrix(const Vector2& x, const Vector2& y, const Vector2& z)
    {
        return Matrix4x4( 2 / (x[1] - x[0]),              0,                              0,                 0,
                          0,                              2 / (y[0] - y[1]),              0,                 0,
                          0,                              0,                             -2 / (z[1] - z[0]), 0,
                         -(x[1] + x[0]) / (x[1] - x[0]), -(y[0] + y[1]) / (y[0] - y[1]),  0,                 1);
    }

    Matrix4x4 OrthoMatrix(const Vector2& x, const Vector2& y)
    {
        return OrthoMatrix(x, y, Vector2(0.1f, 100.0f));
    }

    Matrix4x4 TranslateMatrix(const Vector3& vec)
    {
        return Matrix4x4(1,       0,       0,       0,
                         0,       1,       0,       0,
                         0,       0,       1,       0,
                         vec.X(), vec.Y(), vec.Z(), 1);
    }

    Matrix4x4 TranslateMatrix(const Vector2& vec)
    {
        return TranslateMatrix(Vector3(vec, 0.0f));
    }

    Matrix4x4 RotateXMatrix(const float angle)
    {
        float s = Math::Sin(angle);
        float c = Math::Cos(angle);

        return Matrix4x4(1,  0, 0, 0,
                         0,  c, s, 0,
                         0, -s, c, 0,
                         0,  0, 0, 1);
    }

    Matrix4x4 RotateYMatrix(const float angle)
    {
        float s = Math::Sin(angle);
        float c = Math::Cos(angle);

        return Matrix4x4(c, 0, -s, 0,
                         0, 1,  0, 0,
                         s, 0,  c, 0,
                         0, 0,  0, 1);
    }

    Matrix4x4 RotateZMatrix(const float angle)
    {
        float s = Math::Sin(angle);
        float c = Math::Cos(angle);

        return Matrix4x4( c, s, 0, 0,
                         -s, c, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
    }

    Matrix4x4 RotateMatrix(const Vector3& vec)
    {
        return RotateXMatrix(vec.X()) * RotateYMatrix(vec.Y()) * RotateZMatrix(vec.Z());
    }

    Matrix4x4 ScaleMatrix(const Vector3& vec)
    {
        return Matrix4x4(vec.X(), 0,       0,       0,
                         0,       vec.Y(), 0,       0,
                         0,       0,       vec.Z(), 0,
                         0,       0,       0,       1);
    }

    Matrix4x4 ScaleMatrix(const Vector2& vec)
    {
        return ScaleMatrix(Vector3(vec, 1.0f));
    }

    Matrix4x4 TransformMatrix(const Vector3& translate, const Vector3& rotate, const Vector3& scale)
    {
        return TranslateMatrix(translate) * RotateMatrix(rotate) * ScaleMatrix(scale);
    }

    Matrix4x4 TransformMatrix(const Vector2& translate, const float rotate, const Vector2& scale)
    {
        return TranslateMatrix(translate) * RotateZMatrix(rotate) * ScaleMatrix(scale);
    }
}