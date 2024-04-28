#ifndef VIOLET_ENGINE_MATH_HPP
#define VIOLET_ENGINE_MATH_HPP

namespace Violet
{
    namespace Math
    {
        constexpr double Pi = 3.14159265358979323846;

        extern float  Sin     (const float angle);
        extern double Sin     (const double angle);
        extern float  Cos     (const float angle);
        extern double Cos     (const double angle);
        extern float  SinDeg  (const float angle);
        extern double SinDeg  (const double angle);
        extern float  CosDeg  (const float angle);
        extern double CosDeg  (const double angle);
        extern float  DegToRad(const float degrees);
        extern double DegToRad(const double degrees);
        extern float  RadToDeg(const float radians);
        extern double RadToDeg(const double radians);
    }
}

#endif // VIOLET_ENGINE_MATH_HPP