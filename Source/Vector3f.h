#pragma once

#include <iostream>

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
    class Vector3f
    {
    public:
        const static Vector3f Zero;
        const static Vector3f Up;

        float x, y, z;

        Vector3f() : x(0), y(0), z(0) {}
        Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
        Vector3f(float xyz) : x(xyz), y(xyz), z(xyz) {}

        inline void set(float x, float y, float z);
        inline void set(const Vector3f& v);
        inline Vector3f& normalize();

        inline float sqrMagnitude() const;
        inline float length() const;

        /* Operator overloads */
        inline bool operator==(const Vector3f& v) const;
        inline bool operator!=(const Vector3f& v) const;
        inline float& operator[](size_t pos);
        inline const float& operator[](size_t pos) const;

        inline Vector3f& operator+=(const Vector3f& v);
        inline Vector3f& operator-=(const Vector3f& v);
        inline Vector3f& operator*=(const Vector3f& v);
        inline Vector3f& operator/=(const Vector3f& v);

        inline Vector3f& operator+=(const float f);
        inline Vector3f& operator-=(const float f);
        inline Vector3f& operator*=(const float f);
        inline Vector3f& operator/=(const float f);

        inline Vector3f operator+(const Vector3f& v) const;
        inline Vector3f operator-(const Vector3f& v) const;
        inline Vector3f operator*(const Vector3f& v) const;
        inline Vector3f operator/(const Vector3f& v) const;

        inline Vector3f operator+(const float f) const;
        inline Vector3f operator-(const float f) const;
        inline Vector3f operator*(const float f) const;
        inline Vector3f operator/(const float f) const;

        inline Vector3f operator-() const;
    };

    float dot(const Vector3f& v1, const Vector3f& v2);
    Vector3f cross(const Vector3f& v1, const Vector3f& v2);
    Vector3f normalize(const Vector3f& v);
    Vector3f pow(const Vector3f& v, float exponent);
    float min(const Vector3f& v);
    float max(const Vector3f& v);

    std::ostream& operator<<(std::ostream& os, const Vector3f& v);
#ifdef GDT_NAMESPACE
}
#endif

#include "Vector3f.inl"
