#include "violet_engine_internal.hpp"

namespace Violet
{
	Matrix4x4::Matrix4x4(const float value)
    {
        this->data[0]  = value;
        this->data[1]  = value;
        this->data[2]  = value;
        this->data[3]  = value;
        this->data[4]  = value;
        this->data[5]  = value;
        this->data[6]  = value;
        this->data[7]  = value;
        this->data[8]  = value;
        this->data[9]  = value;
        this->data[10] = value;
        this->data[11] = value;
        this->data[12] = value;
        this->data[13] = value;
        this->data[14] = value;
        this->data[15] = value;
    }

    Matrix4x4::Matrix4x4(const float value1,  const float value2,  const float value3,  const float value4,
                         const float value5,  const float value6,  const float value7,  const float value8,
                         const float value9,  const float value10, const float value11, const float value12,
                         const float value13, const float value14, const float value15, const float value16)
    {
        this->data[0]  = value1;
        this->data[1]  = value2;
        this->data[2]  = value3;
        this->data[3]  = value4;
        this->data[4]  = value5;
        this->data[5]  = value6;
        this->data[6]  = value7;
        this->data[7]  = value8;
        this->data[8]  = value9;
        this->data[9]  = value10;
        this->data[10] = value11;
        this->data[11] = value12;
        this->data[12] = value13;
        this->data[13] = value14;
        this->data[14] = value15;
        this->data[15] = value16;
    }

    Matrix4x4::Matrix4x4(const float arr[16])
    {
        this->data[0]  = arr[0];
        this->data[1]  = arr[1];
        this->data[2]  = arr[2];
        this->data[3]  = arr[3];
        this->data[4]  = arr[4];
        this->data[5]  = arr[5];
        this->data[6]  = arr[6];
        this->data[7]  = arr[7];
        this->data[8]  = arr[8];
        this->data[9]  = arr[9];
        this->data[10] = arr[10];
        this->data[11] = arr[11];
        this->data[12] = arr[12];
        this->data[13] = arr[13];
        this->data[14] = arr[14];
        this->data[15] = arr[15];
    }

    Matrix4x4::Matrix4x4(const Vector4D& vec1, const Vector4D& vec2, const Vector4D& vec3, const Vector4D& vec4)
    {
        this->data[0]  = vec1[0];
        this->data[1]  = vec1[1];
        this->data[2]  = vec1[2];
        this->data[3]  = vec1[3];
        this->data[4]  = vec2[0];
        this->data[5]  = vec2[1];
        this->data[6]  = vec2[2];
        this->data[7]  = vec2[3];
        this->data[8]  = vec3[0];
        this->data[9]  = vec3[1];
        this->data[10] = vec3[2];
        this->data[11] = vec3[3];
        this->data[12] = vec4[0];
        this->data[13] = vec4[1];
        this->data[14] = vec4[2];
        this->data[15] = vec4[3];
    }

    Matrix4x4::Matrix4x4(const Matrix4x4& mat)
    {
        this->data[0]  = mat.data[0];
        this->data[1]  = mat.data[1];
        this->data[2]  = mat.data[2];
        this->data[3]  = mat.data[3];
        this->data[4]  = mat.data[4];
        this->data[5]  = mat.data[5];
        this->data[6]  = mat.data[6];
        this->data[7]  = mat.data[7];
        this->data[8]  = mat.data[8];
        this->data[9]  = mat.data[9];
        this->data[10] = mat.data[10];
        this->data[11] = mat.data[11];
        this->data[12] = mat.data[12];
        this->data[13] = mat.data[13];
        this->data[14] = mat.data[14];
        this->data[15] = mat.data[15];
    }

    Matrix4x4& Matrix4x4::operator=(const float value)
    {
        this->data[0]  = value;
        this->data[1]  = value;
        this->data[2]  = value;
        this->data[3]  = value;
        this->data[4]  = value;
        this->data[5]  = value;
        this->data[6]  = value;
        this->data[7]  = value;
        this->data[8]  = value;
        this->data[9]  = value;
        this->data[10] = value;
        this->data[11] = value;
        this->data[12] = value;
        this->data[13] = value;
        this->data[14] = value;
        this->data[15] = value;
        return *this;
    }

    Matrix4x4& Matrix4x4::operator=(const Matrix4x4& mat)
    {
        this->data[0]  = mat.data[0];
        this->data[1]  = mat.data[1];
        this->data[2]  = mat.data[2];
        this->data[3]  = mat.data[3];
        this->data[4]  = mat.data[4];
        this->data[5]  = mat.data[5];
        this->data[6]  = mat.data[6];
        this->data[7]  = mat.data[7];
        this->data[8]  = mat.data[8];
        this->data[9]  = mat.data[9];
        this->data[10] = mat.data[10];
        this->data[11] = mat.data[11];
        this->data[12] = mat.data[12];
        this->data[13] = mat.data[13];
        this->data[14] = mat.data[14];
        this->data[15] = mat.data[15];
        return *this;
    }

    Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mat) const
    {
        return Matrix4x4(
            (this->data[0]  + mat.data[0]),
            (this->data[1]  + mat.data[1]),
            (this->data[2]  + mat.data[2]),
            (this->data[3]  + mat.data[3]),
            (this->data[4]  + mat.data[4]),
            (this->data[5]  + mat.data[5]),
            (this->data[6]  + mat.data[6]),
            (this->data[7]  + mat.data[7]),
            (this->data[8]  + mat.data[8]),
            (this->data[9]  + mat.data[9]),
            (this->data[10] + mat.data[10]),
            (this->data[11] + mat.data[11]),
            (this->data[12] + mat.data[12]),
            (this->data[13] + mat.data[13]),
            (this->data[14] + mat.data[14]),
            (this->data[15] + mat.data[15])
        );
    }

    Matrix4x4 Matrix4x4::operator-(const Matrix4x4& mat) const
    {
        return Matrix4x4(
            (this->data[0]  - mat.data[0]),
            (this->data[1]  - mat.data[1]),
            (this->data[2]  - mat.data[2]),
            (this->data[3]  - mat.data[3]),
            (this->data[4]  - mat.data[4]),
            (this->data[5]  - mat.data[5]),
            (this->data[6]  - mat.data[6]),
            (this->data[7]  - mat.data[7]),
            (this->data[8]  - mat.data[8]),
            (this->data[9]  - mat.data[9]),
            (this->data[10] - mat.data[10]),
            (this->data[11] - mat.data[11]),
            (this->data[12] - mat.data[12]),
            (this->data[13] - mat.data[13]),
            (this->data[14] - mat.data[14]),
            (this->data[15] - mat.data[15])
        );
    }

    Vector4D Matrix4x4::operator*(const Vector4D& vec) const
    {
        return Vector4D(
            (this->data[0] * vec.data[0]) + (this->data[4] * vec.data[1]) + (this->data[8]  * vec.data[2]) + (this->data[12] * vec.data[3]),
            (this->data[1] * vec.data[0]) + (this->data[5] * vec.data[1]) + (this->data[9]  * vec.data[2]) + (this->data[13] * vec.data[3]),
            (this->data[2] * vec.data[0]) + (this->data[6] * vec.data[1]) + (this->data[10] * vec.data[2]) + (this->data[14] * vec.data[3]),
            (this->data[3] * vec.data[0]) + (this->data[7] * vec.data[1]) + (this->data[11] * vec.data[2]) + (this->data[15] * vec.data[3])
        );
    }

    Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const
    {
        return Matrix4x4(
            (this->data[0] * mat.data[0])  + (this->data[4] * mat.data[1])  + (this->data[8]  * mat.data[2])  + (this->data[12] * mat.data[3]),
            (this->data[1] * mat.data[0])  + (this->data[5] * mat.data[1])  + (this->data[9]  * mat.data[2])  + (this->data[13] * mat.data[3]),
            (this->data[2] * mat.data[0])  + (this->data[6] * mat.data[1])  + (this->data[10] * mat.data[2])  + (this->data[14] * mat.data[3]),
            (this->data[3] * mat.data[0])  + (this->data[7] * mat.data[1])  + (this->data[11] * mat.data[2])  + (this->data[15] * mat.data[3]),
            (this->data[0] * mat.data[4])  + (this->data[4] * mat.data[5])  + (this->data[8]  * mat.data[6])  + (this->data[12] * mat.data[7]),
            (this->data[1] * mat.data[4])  + (this->data[5] * mat.data[5])  + (this->data[9]  * mat.data[6])  + (this->data[13] * mat.data[7]),
            (this->data[2] * mat.data[4])  + (this->data[6] * mat.data[5])  + (this->data[10] * mat.data[6])  + (this->data[14] * mat.data[7]),
            (this->data[3] * mat.data[4])  + (this->data[7] * mat.data[5])  + (this->data[11] * mat.data[6])  + (this->data[15] * mat.data[7]),
            (this->data[0] * mat.data[8])  + (this->data[4] * mat.data[9])  + (this->data[8]  * mat.data[10]) + (this->data[12] * mat.data[11]),
            (this->data[1] * mat.data[8])  + (this->data[5] * mat.data[9])  + (this->data[9]  * mat.data[10]) + (this->data[13] * mat.data[11]),
            (this->data[2] * mat.data[8])  + (this->data[6] * mat.data[9])  + (this->data[10] * mat.data[10]) + (this->data[14] * mat.data[11]),
            (this->data[3] * mat.data[8])  + (this->data[7] * mat.data[9])  + (this->data[11] * mat.data[10]) + (this->data[15] * mat.data[11]),
            (this->data[0] * mat.data[12]) + (this->data[4] * mat.data[13]) + (this->data[8]  * mat.data[14]) + (this->data[12] * mat.data[15]),
            (this->data[1] * mat.data[12]) + (this->data[5] * mat.data[13]) + (this->data[9]  * mat.data[14]) + (this->data[13] * mat.data[15]),
            (this->data[2] * mat.data[12]) + (this->data[6] * mat.data[13]) + (this->data[10] * mat.data[14]) + (this->data[14] * mat.data[15]),
            (this->data[3] * mat.data[12]) + (this->data[7] * mat.data[13]) + (this->data[11] * mat.data[14]) + (this->data[15] * mat.data[15])
        );
    }

    Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& mat)
    {
        this->data[0]  += mat.data[0];
        this->data[1]  += mat.data[1];
        this->data[2]  += mat.data[2];
        this->data[3]  += mat.data[3];
        this->data[4]  += mat.data[4];
        this->data[5]  += mat.data[5];
        this->data[6]  += mat.data[6];
        this->data[7]  += mat.data[7];
        this->data[8]  += mat.data[8];
        this->data[9]  += mat.data[9];
        this->data[10] += mat.data[10];
        this->data[11] += mat.data[11];
        this->data[12] += mat.data[12];
        this->data[13] += mat.data[13];
        this->data[14] += mat.data[14];
        this->data[15] += mat.data[15];
        return *this;
    }

    Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& mat)
    {
        this->data[0]  -= mat.data[0];
        this->data[1]  -= mat.data[1];
        this->data[2]  -= mat.data[2];
        this->data[3]  -= mat.data[3];
        this->data[4]  -= mat.data[4];
        this->data[5]  -= mat.data[5];
        this->data[6]  -= mat.data[6];
        this->data[7]  -= mat.data[7];
        this->data[8]  -= mat.data[8];
        this->data[9]  -= mat.data[9];
        this->data[10] -= mat.data[10];
        this->data[11] -= mat.data[11];
        this->data[12] -= mat.data[12];
        this->data[13] -= mat.data[13];
        this->data[14] -= mat.data[14];
        this->data[15] -= mat.data[15];
        return *this;
    }

    Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& mat)
    {
        this->data[0]  = (this->data[0] * mat.data[0])  + (this->data[4] * mat.data[1])  + (this->data[8]  * mat.data[2])  + (this->data[12] * mat.data[3]);
        this->data[1]  = (this->data[1] * mat.data[0])  + (this->data[5] * mat.data[1])  + (this->data[9]  * mat.data[2])  + (this->data[13] * mat.data[3]);
        this->data[2]  = (this->data[2] * mat.data[0])  + (this->data[6] * mat.data[1])  + (this->data[10] * mat.data[2])  + (this->data[14] * mat.data[3]);
        this->data[3]  = (this->data[3] * mat.data[0])  + (this->data[7] * mat.data[1])  + (this->data[11] * mat.data[2])  + (this->data[15] * mat.data[3]);
        this->data[4]  = (this->data[0] * mat.data[4])  + (this->data[4] * mat.data[5])  + (this->data[8]  * mat.data[6])  + (this->data[12] * mat.data[7]);
        this->data[5]  = (this->data[1] * mat.data[4])  + (this->data[5] * mat.data[5])  + (this->data[9]  * mat.data[6])  + (this->data[13] * mat.data[7]);
        this->data[6]  = (this->data[2] * mat.data[4])  + (this->data[6] * mat.data[5])  + (this->data[10] * mat.data[6])  + (this->data[14] * mat.data[7]);
        this->data[7]  = (this->data[3] * mat.data[4])  + (this->data[7] * mat.data[5])  + (this->data[11] * mat.data[6])  + (this->data[15] * mat.data[7]);
        this->data[8]  = (this->data[0] * mat.data[8])  + (this->data[4] * mat.data[9])  + (this->data[8]  * mat.data[10]) + (this->data[12] * mat.data[11]);
        this->data[9]  = (this->data[1] * mat.data[8])  + (this->data[5] * mat.data[9])  + (this->data[9]  * mat.data[10]) + (this->data[13] * mat.data[11]);
        this->data[10] = (this->data[2] * mat.data[8])  + (this->data[6] * mat.data[9])  + (this->data[10] * mat.data[10]) + (this->data[14] * mat.data[11]);
        this->data[11] = (this->data[3] * mat.data[8])  + (this->data[7] * mat.data[9])  + (this->data[11] * mat.data[10]) + (this->data[15] * mat.data[11]);
        this->data[12] = (this->data[0] * mat.data[12]) + (this->data[4] * mat.data[13]) + (this->data[8]  * mat.data[14]) + (this->data[12] * mat.data[15]);
        this->data[13] = (this->data[1] * mat.data[12]) + (this->data[5] * mat.data[13]) + (this->data[9]  * mat.data[14]) + (this->data[13] * mat.data[15]);
        this->data[14] = (this->data[2] * mat.data[12]) + (this->data[6] * mat.data[13]) + (this->data[10] * mat.data[14]) + (this->data[14] * mat.data[15]);
        this->data[15] = (this->data[3] * mat.data[12]) + (this->data[7] * mat.data[13]) + (this->data[11] * mat.data[14]) + (this->data[15] * mat.data[15]);
        return *this;
    }

    Matrix4x4 Matrix4x4::Identity()
    {
        return Matrix4x4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );
    }

    Matrix4x4 OrthoMatrix(const Vector2D& x, const Vector2D& y, const Vector2D& z)
    {
        return Matrix4x4(
             2 / (x[1] - x[0]),              0,                              0,                 0,
             0,                              2 / (y[0] - y[1]),              0,                 0,
             0,                              0,                             -2 / (z[1] - z[0]), 0,
            -(x[1] + x[0]) / (x[1] - x[0]), -(y[0] + y[1]) / (y[0] - y[1]),  0,                 1
        );
    }

    Matrix4x4 OrthoMatrix(const Vector2D& x, const Vector2D& y)
    {
        return OrthoMatrix(x, y, Vector2D(0.1f, 100.0f));
    }

    Matrix4x4 TranslateMatrix(const Vector3D& vec)
    {
        return Matrix4x4(
            1,       0,       0,       0,
            0,       1,       0,       0,
            0,       0,       1,       0,
            vec.X(), vec.Y(), vec.Z(), 1
        );
    }

    Matrix4x4 TranslateMatrix(const Vector2D& vec)
    {
        return TranslateMatrix(Vector3D(vec, 0.0f));
    }

    Matrix4x4 RotateXMatrix(const float angle)
    {
        float s = Math::Sin(angle);
        float c = Math::Cos(angle);

        return Matrix4x4(
            1,  0, 0, 0,
            0,  c, s, 0,
            0, -s, c, 0,
            0,  0, 0, 1
        );
    }

    Matrix4x4 RotateYMatrix(const float angle)
    {
        float s = Math::Sin(angle);
        float c = Math::Cos(angle);

        return Matrix4x4(
            c, 0, -s, 0,
            0, 1,  0, 0,
            s, 0,  c, 0,
            0, 0,  0, 1
        );
    }

    Matrix4x4 RotateZMatrix(const float angle)
    {
        float s = Math::Sin(angle);
        float c = Math::Cos(angle);

        return Matrix4x4(
             c, s, 0, 0,
            -s, c, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 1
        );
    }

    Matrix4x4 RotateMatrix(const Vector3D& vec)
    {
        return RotateXMatrix(vec.X()) * RotateYMatrix(vec.Y()) * RotateZMatrix(vec.Z());
    }

    Matrix4x4 ScaleMatrix(const Vector3D& vec)
    {
        return Matrix4x4(
            vec.X(), 0,       0,       0,
            0,       vec.Y(), 0,       0,
            0,       0,       vec.Z(), 0,
            0,       0,       0,       1
        );
    }

    Matrix4x4 ScaleMatrix(const Vector2D& vec)
    {
        return ScaleMatrix(Vector3D(vec, 1.0f));
    }

    Matrix4x4 TransformMatrix(const Vector3D& translate, const Vector3D& rotate, const Vector3D& scale)
    {
        return TranslateMatrix(translate) * RotateMatrix(rotate) * ScaleMatrix(scale);
    }

    Matrix4x4 TransformMatrix(const Vector2D& translate, const float rotate, const Vector2D& scale)
    {
        return TranslateMatrix(translate) * RotateZMatrix(rotate) * ScaleMatrix(scale);
    }
}