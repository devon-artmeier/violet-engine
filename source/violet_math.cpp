#include "violet_engine_internal.hpp"

namespace Violet
{
    namespace Math
    {
        float Sin(const float angle)
        {
            return sinf(angle);
        }

        double Sin(const double angle)
        {
            return sin(angle);
        }

        float Cos(const float angle)
        {
            return cosf(angle);
        }

        double Cos(const double angle)
        {
            return cos(angle);
        }

        float SinDegrees(const float angle)
        {
            return sinf(Radians(angle));
        }

        double SinDegrees(const double angle)
        {
            return sin(Radians(angle));
        }

        float CosDegrees(const float angle)
        {
            return cosf(Radians(angle));
        }

        double CosDegrees(const double angle)
        {
            return cos(Radians(angle));
        }

        float Radians(const float degrees)
        {
            return degrees * (static_cast<float>(Pi) / 180.0f);
        }

        double Radians(const double degrees)
        {
            return degrees * (Pi / 180.0);
        }

        float Degrees(const float radians)
        {
            return radians * (180.0f / static_cast<float>(Pi));
        }

        double Degrees(const double radians)
        {
            return radians * (180.0 / Pi);
        }
    }
}