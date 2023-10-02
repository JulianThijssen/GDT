#pragma once

#include <iostream>

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
    class Vector3f;

    class Vector4f
    {
    public:
        const static Vector4f Zero;
        const static Vector4f Up;

        union
        {
            struct { float x, y, z, w; };
            float a[4];
        };

        Vector4f();
        Vector4f(float x, float y, float z, float w);
        Vector4f(float xyz);
        Vector4f(float xyz, float w);
        Vector4f(Vector3f v, float w);

        inline void set(float x, float y, float z, float w);
        inline void set(const Vector4f& v);
        inline Vector4f& normalize();

        inline float sqrMagnitude() const;
        inline float length() const;

        /* Operator overloads */
        inline bool operator==(const Vector4f& v) const;
        inline bool operator!=(const Vector4f& v) const;
        inline float& operator[](size_t pos);
        inline const float& operator[](size_t pos) const;

        inline Vector4f& operator+=(const Vector4f& v);
        inline Vector4f& operator-=(const Vector4f& v);
        inline Vector4f& operator*=(const Vector4f& v);
        inline Vector4f& operator/=(const Vector4f& v);

        inline Vector4f& operator+=(const float f);
        inline Vector4f& operator-=(const float f);
        inline Vector4f& operator*=(const float f);
        inline Vector4f& operator/=(const float f);

        inline Vector4f operator+(const Vector4f& v) const;
        inline Vector4f operator-(const Vector4f& v) const;
        inline Vector4f operator*(const Vector4f& v) const;
        inline Vector4f operator/(const Vector4f& v) const;

        inline Vector4f operator+(const float f);
        inline Vector4f operator-(const float f);
        inline Vector4f operator*(const float f);
        inline Vector4f operator/(const float f);

        inline Vector4f operator-() const;
    };

    float dot(const Vector4f& v1, const Vector4f& v2);
    Vector4f cross(const Vector4f& v1, const Vector4f& v2);
    Vector4f normalize(const Vector4f& v);
    Vector4f pow(const Vector4f& v, float exponent);
    Vector4f mix(const Vector4f& v1, const Vector4f& v2, float a);
    float min(const Vector4f& v);
    float max(const Vector4f& v);

    std::ostream& operator<<(std::ostream& os, const Vector4f& v);
#ifdef GDT_NAMESPACE
}
#endif

#include "Vector4f.inl"
