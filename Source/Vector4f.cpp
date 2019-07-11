#include "Vector4f.h"

#include "Vector3f.h"
#include "Math.h"
#include <cmath>

Vector4f::Vector4f()
{
    set(0, 0, 0, 1);
}

Vector4f::Vector4f(float x, float y, float z, float w)
{
    set(x, y, z, w);
}

Vector4f::Vector4f(float xyz)
{
    set(xyz, xyz, xyz, 1);
}

Vector4f::Vector4f(float xyz, float w)
{
    set(xyz, xyz, xyz, w);
}

Vector4f::Vector4f(Vector3f v, float w)
{
    set(v.x, v.y, v.z, w);
}

void Vector4f::set(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void Vector4f::set(const Vector4f& v)
{
    set(v.x, v.y, v.z, v.w);
}

Vector4f& Vector4f::normalize()
{
    float l = length();

    x /= l;
    y /= l;
    z /= l;
    return *this;
}

float Vector4f::sqrMagnitude() const
{
    return x*x + y*y + z*z;
}

float Vector4f::length() const
{
    return sqrt(sqrMagnitude());
}

/* Operator overloads */
bool Vector4f::operator==(const Vector4f& v) const
{
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool Vector4f::operator!=(const Vector4f& v) const
{
    return x != v.x || y != v.y || z != v.z || w != v.w;
}

float& Vector4f::operator[](size_t pos)
{
    switch (pos)
    {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
        throw std::out_of_range(std::string("Attempting to access component ") + std::to_string(pos) + std::string(" of Vector4f, only [0-3] are defined."));
    }
}

const float& Vector4f::operator[](size_t pos) const
{
    switch (pos)
    {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
        throw std::out_of_range(std::string("Attempting to access component ") + std::to_string(pos) + std::string(" of Vector4f, only [0-3] are defined."));
    }
}

Vector4f& Vector4f::operator+=(const Vector4f& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector4f& Vector4f::operator-=(const Vector4f& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector4f& Vector4f::operator*=(const Vector4f& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vector4f& Vector4f::operator/=(const Vector4f& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

Vector4f& Vector4f::operator+=(const float f)
{
    x += f;
    y += f;
    z += f;
    return *this;
}

Vector4f& Vector4f::operator-=(const float f)
{
    x -= f;
    y -= f;
    z -= f;
    return *this;
}

Vector4f& Vector4f::operator*=(const float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Vector4f& Vector4f::operator/=(const float f)
{
    x /= f;
    y /= f;
    z /= f;
    return *this;
}


Vector4f Vector4f::operator+(const Vector4f& v) const
{
    return Vector4f(x + v.x, y + v.y, z + v.z, w);
}

Vector4f Vector4f::operator-(const Vector4f& v) const
{
    return Vector4f(x - v.x, y - v.y, z - v.z, w);
}

Vector4f Vector4f::operator*(const Vector4f& v) const
{
    return Vector4f(x * v.x, y * v.y, z * v.z, w);
}

Vector4f Vector4f::operator/(const Vector4f& v) const
{
    return Vector4f(x / v.x, y / v.y, z / v.z, w);
}


Vector4f Vector4f::operator+(const float f)
{
    return Vector4f(x + f, y + f, z + f, w);
}

Vector4f Vector4f::operator-(const float f)
{
    return Vector4f(x - f, y - f, z - f, w);
}

Vector4f Vector4f::operator*(const float f)
{
    return Vector4f(x * f, y * f, z * f, w);
}

Vector4f Vector4f::operator/(const float f)
{
    return Vector4f(x / f, y / f, z / f, w);
}

Vector4f Vector4f::operator-() const
{
    return Vector4f(-x, -y, -z, w);
}

float dot(const Vector4f& v1, const Vector4f& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector4f cross(const Vector4f& v1, const Vector4f& v2)
{
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v2.x * v1.z - v2.z * v1.x;
    float z = v1.x * v2.y - v1.y * v2.x;
    return Vector4f(x, y, z, v1.w);
}

Vector4f normalize(const Vector4f& v)
{
    float l = v.length();

    return Vector4f(v.x / l, v.y / l, v.z / l, v.w);
}

Vector4f pow(const Vector4f& v, float exponent)
{
    return Vector4f(powf(v.x, exponent), powf(v.y, exponent), powf(v.z, exponent), v.w);
}

Vector4f mix(const Vector4f& v1, const Vector4f& v2, float a)
{
    return v1 * (1 - a) + v2 * a;
}

float min(const Vector4f& v)
{
    return Math::min(v.x, Math::min(v.y, v.z));
}

float max(const Vector4f& v)
{
    return Math::max(v.x, Math::max(v.y, v.z));
}

std::ostream& operator<<(std::ostream& os, const Vector4f& v)
{
    os << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
    return os;
}
