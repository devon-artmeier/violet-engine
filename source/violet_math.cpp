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

        float SinDeg(const float angle)
        {
            return sinf(DegToRad(angle));
        }

        double SinDeg(const double angle)
        {
            return sin(DegToRad(angle));
        }

        float CosDeg(const float angle)
        {
            return cosf(DegToRad(angle));
        }

        double CosDeg(const double angle)
        {
            return cos(DegToRad(angle));
        }

        float DegToRad(const float degrees)
        {
            return degrees * (static_cast<float>(Pi) / 180.0f);
        }

        double DegToRad(const double degrees)
        {
            return degrees * (Pi / 180.0);
        }

        float RadToDeg(const float radians)
        {
            return radians * (180.0f / static_cast<float>(Pi));
        }

        double RadToDeg(const double radians)
        {
            return radians * (180.0 / Pi);
        }
    }
}