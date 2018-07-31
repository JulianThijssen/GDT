#include "Vector2f.h"

#include <cmath>

Vector2f::Vector2f()
{
    set(0, 0);
}

Vector2f::Vector2f(float x, float y)
{
    set(x, y);
}

Vector2f::Vector2f(float xy)
{
    set(xy, xy);
}

void Vector2f::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vector2f::set(const Vector2f& v)
{
    set(v.x, v.y);
}

Vector2f& Vector2f::normalize()
{
    float l = length();

    x /= l;
    y /= l;
    return *this;
}

float Vector2f::sqrMagnitude() const
{
    return x*x + y*y;
}

float Vector2f::length() const
{
    return sqrt(sqrMagnitude());
}

/* Operator overloads */
bool Vector2f::operator==(const Vector2f& v) const
{
    return x == v.x && y == v.y;
}

bool Vector2f::operator!=(const Vector2f& v) const
{
    return x != v.x || y != v.y;
}

Vector2f& Vector2f::operator+=(const Vector2f& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2f& Vector2f::operator*=(const Vector2f& v)
{
    x *= v.x;
    y *= v.y;
    return *this;
}

Vector2f& Vector2f::operator/=(const Vector2f& v)
{
    x /= v.x;
    y /= v.y;
    return *this;
}

Vector2f& Vector2f::operator+=(const float f)
{
    x += f;
    y += f;
    return *this;
}

Vector2f& Vector2f::operator-=(const float f)
{
    x -= f;
    y -= f;
    return *this;
}

Vector2f& Vector2f::operator*=(const float f)
{
    x *= f;
    y *= f;
    return *this;
}

Vector2f& Vector2f::operator/=(const float f)
{
    x /= f;
    y /= f;
    return *this;
}


Vector2f Vector2f::operator+(const Vector2f& v) const
{
    return Vector2f(x + v.x, y + v.y);
}

Vector2f Vector2f::operator-(const Vector2f& v) const
{
    return Vector2f(x - v.x, y - v.y);
}

Vector2f Vector2f::operator*(const Vector2f& v) const
{
    return Vector2f(x * v.x, y * v.y);
}

Vector2f Vector2f::operator/(const Vector2f& v) const
{
    return Vector2f(x / v.x, y / v.y);
}


Vector2f Vector2f::operator+(const float f)
{
    return Vector2f(x + f, y + f);
}

Vector2f Vector2f::operator-(const float f)
{
    return Vector2f(x - f, y - f);
}

Vector2f Vector2f::operator*(const float f)
{
    return Vector2f(x * f, y * f);
}

Vector2f Vector2f::operator/(const float f)
{
    return Vector2f(x / f, y / f);
}

Vector2f Vector2f::operator-() const
{
    return Vector2f(-x, -y);
}

float dot(const Vector2f& v1, const Vector2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

Vector2f normalize(const Vector2f& v)
{
    float l = v.length();

    return Vector2f(v.x / l, v.y / l);
}

Vector2f pow(const Vector2f& v, float exponent)
{
    return Vector2f(powf(v.x, exponent), powf(v.y, exponent));
}

std::ostream& operator<<(std::ostream& os, const Vector2f& v)
{
    os << '(' << v.x << ", " << v.y << ')';
    return os;
}
