#ifndef VIOLET_ENGINE_MATH_HPP
#define VIOLET_ENGINE_MATH_HPP

namespace Violet
{
    namespace Math
    {
        constexpr double Pi = 3.14159265358979323846;

        extern float  Sin       (const float angle);
        extern double Sin       (const double angle);
        extern float  Cos       (const float angle);
        extern double Cos       (const double angle);
        extern float  SinDegrees(const float angle);
        extern double SinDegrees(const double angle);
        extern float  CosDegrees(const float angle);
        extern double CosDegrees(const double angle);
        extern float  Radians   (const float degrees);
        extern double Radians   (const double degrees);
        extern float  Degrees   (const float radians);
        extern double Degrees   (const double radians);
    }
}

#endif // VIOLET_ENGINE_MATH_HPP