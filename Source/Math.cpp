#include "Math.h"

namespace GDT
{
    namespace Math
    {
        float min(float f1, float f2)
        {
            return f1 < f2 ? f1 : f2;
        }

        float max(float f1, float f2)
        {
            return f1 > f2 ? f1 : f2;
        }

        float toDegrees(const float radians)
        {
            return radians * (180 / PI);
        }

        float toRadians(const float degrees)
        {
            return degrees * (PI / 180);
        }
    }
}
