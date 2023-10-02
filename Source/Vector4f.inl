#include <string>

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
    float il = 1 / length();

    x *= il;
    y *= il;
    z *= il;
    return *this;
}

float Vector4f::sqrMagnitude() const
{
    return x * x + y * y + z * z;
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
    return a[pos];
}

const float& Vector4f::operator[](size_t pos) const
{
    return a[pos];
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
