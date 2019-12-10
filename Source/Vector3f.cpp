#include "Vector3f.h"

#include "Math.h"

#include <string>
#include <cmath>

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
    Vector3f::Vector3f()
    {
        set(0, 0, 0);
    }

    Vector3f::Vector3f(float x, float y, float z)
    {
        set(x, y, z);
    }

    Vector3f::Vector3f(float xyz)
    {
        set(xyz, xyz, xyz);
    }

    void Vector3f::set(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Vector3f::set(const Vector3f& v)
    {
        set(v.x, v.y, v.z);
    }

    Vector3f& Vector3f::normalize()
    {
        float l = length();

        x /= l;
        y /= l;
        z /= l;
        return *this;
    }

    float Vector3f::sqrMagnitude() const
    {
        return x * x + y * y + z * z;
    }

    float Vector3f::length() const
    {
        return sqrt(sqrMagnitude());
    }

    /* Operator overloads */
    bool Vector3f::operator==(const Vector3f& v) const
    {
        return x == v.x && y == v.y && z == v.z;
    }

    bool Vector3f::operator!=(const Vector3f& v) const
    {
        return x != v.x || y != v.y || z != v.z;
    }

    float& Vector3f::operator[](size_t pos)
    {
        switch (pos)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        }

        throw std::out_of_range(std::string("Attempting to access component ") + std::to_string(pos) + std::string(" of Vector3f, only [0-2] are defined."));
    }

    const float& Vector3f::operator[](size_t pos) const
    {
        switch (pos)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        }
        throw std::out_of_range(std::string("Attempting to access component ") + std::to_string(pos) + std::string(" of Vector3f, only [0-2] are defined."));
    }

    Vector3f& Vector3f::operator+=(const Vector3f& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3f& Vector3f::operator-=(const Vector3f& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3f& Vector3f::operator*=(const Vector3f& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    Vector3f& Vector3f::operator/=(const Vector3f& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    Vector3f& Vector3f::operator+=(const float f)
    {
        x += f;
        y += f;
        z += f;
        return *this;
    }

    Vector3f& Vector3f::operator-=(const float f)
    {
        x -= f;
        y -= f;
        z -= f;
        return *this;
    }

    Vector3f& Vector3f::operator*=(const float f)
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    Vector3f& Vector3f::operator/=(const float f)
    {
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }


    Vector3f Vector3f::operator+(const Vector3f& v) const
    {
        return Vector3f(x + v.x, y + v.y, z + v.z);
    }

    Vector3f Vector3f::operator-(const Vector3f& v) const
    {
        return Vector3f(x - v.x, y - v.y, z - v.z);
    }

    Vector3f Vector3f::operator*(const Vector3f& v) const
    {
        return Vector3f(x * v.x, y * v.y, z * v.z);
    }

    Vector3f Vector3f::operator/(const Vector3f& v) const
    {
        return Vector3f(x / v.x, y / v.y, z / v.z);
    }


    Vector3f Vector3f::operator+(const float f)
    {
        return Vector3f(x + f, y + f, z + f);
    }

    Vector3f Vector3f::operator-(const float f)
    {
        return Vector3f(x - f, y - f, z - f);
    }

    Vector3f Vector3f::operator*(const float f)
    {
        return Vector3f(x * f, y * f, z * f);
    }

    Vector3f Vector3f::operator/(const float f)
    {
        return Vector3f(x / f, y / f, z / f);
    }

    Vector3f Vector3f::operator-() const
    {
        return Vector3f(-x, -y, -z);
    }

    float dot(const Vector3f& v1, const Vector3f& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    Vector3f cross(const Vector3f& v1, const Vector3f& v2)
    {
        float x = v1.y * v2.z - v1.z * v2.y;
        float y = v2.x * v1.z - v2.z * v1.x;
        float z = v1.x * v2.y - v1.y * v2.x;
        return Vector3f(x, y, z);
    }

    Vector3f normalize(const Vector3f& v)
    {
        float l = v.length();

        return Vector3f(v.x / l, v.y / l, v.z / l);
    }

    Vector3f pow(const Vector3f& v, float exponent)
    {
        return Vector3f(powf(v.x, exponent), powf(v.y, exponent), powf(v.z, exponent));
    }

    float min(const Vector3f& v)
    {
        return Math::min(v.x, Math::min(v.y, v.z));
    }

    float max(const Vector3f& v)
    {
        return Math::max(v.x, Math::max(v.y, v.z));
    }

    std::ostream& operator<<(std::ostream& os, const Vector3f& v)
    {
        os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
        return os;
    }
#ifdef GDT_NAMESPACE
}
#endif
