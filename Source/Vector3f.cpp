#include "Vector3f.h"

#include "Maths.h"

#include <string>
#include <cmath>
#include <iomanip>

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
    const Vector3f Vector3f::Zero = Vector3f(0, 0, 0);
    const Vector3f Vector3f::Up = Vector3f(0, 1, 0);

    constexpr float epsilon = 0.00001f;

    Vector3f& Vector3f::normalize()
    {
        float len = length();

        float invl = 0;
        if (len > epsilon)
            invl = 1.0f / length();

        x *= invl;
        y *= invl;
        z *= invl;

        return *this;
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
        float len = v.length();
        if (len > epsilon)
            return v / len;
        
        return Vector3f::Zero;
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

#define __ << std::right << std::setw(5) <<
    std::ostream& operator<<(std::ostream& os, const Vector3f& v)
    {
        os << std::fixed << std::setprecision(2) << '(' __ v.x << ", " __ v.y << ", " __ v.z << ')';
        return os;
    }
#ifdef GDT_NAMESPACE
}
#endif
