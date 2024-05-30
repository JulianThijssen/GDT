#include <string>

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
    float invf = 1.0f / f;
    x *= invf;
    y *= invf;
    z *= invf;
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


Vector3f Vector3f::operator+(const float f) const
{
    return Vector3f(x + f, y + f, z + f);
}

Vector3f Vector3f::operator-(const float f) const
{
    return Vector3f(x - f, y - f, z - f);
}

Vector3f Vector3f::operator*(const float f) const
{
    return Vector3f(x * f, y * f, z * f);
}

Vector3f Vector3f::operator/(const float f) const
{
    float invf = 1.0f / f;
    return Vector3f(x * invf, y * invf, z * invf);
}

Vector3f Vector3f::operator-() const
{
    return Vector3f(-x, -y, -z);
}
