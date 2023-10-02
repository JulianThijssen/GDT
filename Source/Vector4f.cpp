#include "Vector4f.h"

#include "Vector3f.h"
#include "Maths.h"

#include <string>
#include <cmath>

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
    const Vector4f Vector4f::Zero = Vector4f(0, 0, 0, 0);
    const Vector4f Vector4f::Up = Vector4f(0, 1, 0, 0);

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
#ifdef GDT_NAMESPACE
}
#endif
