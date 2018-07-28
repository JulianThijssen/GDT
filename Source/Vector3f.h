#pragma once

class Vector3f
{
public:
    float x, y, z;

    Vector3f();
    Vector3f(float x, float y, float z);
    Vector3f(float xyz);

    void set(float x, float y, float z);
    void set(const Vector3f& v);
    Vector3f& normalize();

    float sqrMagnitude() const;
    float length() const;

    /* Operator overloads */
    bool operator==(const Vector3f& v) const;
    bool operator!=(const Vector3f& v) const;

    Vector3f& operator+=(const Vector3f& v);
    Vector3f& operator-=(const Vector3f& v);
    Vector3f& operator*=(const Vector3f& v);
    Vector3f& operator/=(const Vector3f& v);

    Vector3f& operator+=(const float f);
    Vector3f& operator-=(const float f);
    Vector3f& operator*=(const float f);
    Vector3f& operator/=(const float f);

    Vector3f operator+(const Vector3f& v) const;
    Vector3f operator-(const Vector3f& v) const;
    Vector3f operator*(const Vector3f& v) const;
    Vector3f operator/(const Vector3f& v) const;

    Vector3f operator+(const float f);
    Vector3f operator-(const float f);
    Vector3f operator*(const float f);
    Vector3f operator/(const float f);

    Vector3f operator-() const;
};

float dot(const Vector3f& v1, const Vector3f& v2);
Vector3f cross(const Vector3f& v1, const Vector3f& v2);
Vector3f normalize(const Vector3f& v);
