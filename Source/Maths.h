#pragma once

#include <limits>

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
    namespace Math
    {
        const float PI = 3.14159265359f;
        const float TWO_PI = 2 * 3.14159265359f;
        const float INF = std::numeric_limits<float>::infinity();

        float min(float f1, float f2);
        float max(float f1, float f2);

        float toDegrees(const float radians);
        float toRadians(const float degrees);
    }
#ifdef GDT_NAMESPACE
}
#endif
