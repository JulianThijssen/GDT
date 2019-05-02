#include "Matrix4f.h"

#include "Vector3f.h"
#include "Vector4f.h"
#include "Math.h"

#include <cmath>
#include <sstream>


const Matrix4f Matrix4f::IDENTITY = Matrix4f();
const Matrix4f Matrix4f::BIAS = Matrix4f(0.5f, 0.0f, 0.0f, 0.0f,
                                            0.0f, 0.5f, 0.0f, 0.0f,
                                            0.0f, 0.0f, 0.5f, 0.0f,
                                            0.5f, 0.5f, 0.5f, 1.0f);

/* Core */
Matrix4f::Matrix4f() {
    setIdentity();
}

Matrix4f::Matrix4f(float m0, float m1, float m2, float m3,
                    float m4, float m5, float m6, float m7,
                    float m8, float m9, float m10, float m11,
                    float m12, float m13, float m14, float m15) {
    a[0] = m0;   a[1] = m1;   a[2] = m2;   a[3] = m3;
    a[4] = m4;   a[5] = m5;   a[6] = m6;   a[7] = m7;
    a[8] = m8;   a[9] = m9;   a[10] = m10; a[11] = m11;
    a[12] = m12; a[13] = m13; a[14] = m14; a[15] = m15;
}

void Matrix4f::setIdentity() {
    for (int i = 0; i < 16; i++) {
        a[i] = i % 5 == 0 ? 1.0f : 0.0f;
    }
}

void Matrix4f::translate(const Vector3f& v) {
    a[12] += a[0] * v.x + a[4] * v.y + a[8] * v.z;
    a[13] += a[1] * v.x + a[5] * v.y + a[9] * v.z;
    a[14] += a[2] * v.x + a[6] * v.y + a[10] * v.z;
    a[15] += a[3] * v.x + a[7] * v.y + a[11] * v.z;
}

void Matrix4f::rotate(float angle, float x, float y, float z) {
    float c = cos(Math::toRadians(angle));
    float s = sin(Math::toRadians(angle));
    float ic = 1 - c;

    float f0 = a[0] * ((x * x * ic) + c) + a[4] * ((x * y * ic) + (z * s)) + a[8] * ((x * z * ic) - (y * s));
    float f1 = a[1] * ((x * x * ic) + c) + a[5] * ((x * y * ic) + (z * s)) + a[9] * ((x * z * ic) - (y * s));
    float f2 = a[2] * ((x * x * ic) + c) + a[6] * ((x * y * ic) + (z * s)) + a[10] * ((x * z * ic) - (y * s));
    float f3 = a[3] * ((x * x * ic) + c) + a[7] * ((x * y * ic) + (z * s)) + a[11] * ((x * z * ic) - (y * s));

    float f4 = a[0] * ((x * y * ic) - (z * s)) + a[4] * ((y * y * ic) + c) + a[8] * ((y * z * ic) + (x * s));
    float f5 = a[1] * ((x * y * ic) - (z * s)) + a[5] * ((y * y * ic) + c) + a[9] * ((y * z * ic) + (x * s));
    float f6 = a[2] * ((x * y * ic) - (z * s)) + a[6] * ((y * y * ic) + c) + a[10] * ((y * z * ic) + (x * s));
    float f7 = a[3] * ((x * y * ic) - (z * s)) + a[7] * ((y * y * ic) + c) + a[11] * ((y * z * ic) + (x * s));

    float f8 = a[0] * ((x * z * ic) + (y * s)) + a[4] * ((y * z * ic) - (x * s)) + a[8] * ((z * z * ic) + c);
    float f9 = a[1] * ((x * z * ic) + (y * s)) + a[5] * ((y * z * ic) - (x * s)) + a[9] * ((z * z * ic) + c);
    float f10 = a[2] * ((x * z * ic) + (y * s)) + a[6] * ((y * z * ic) - (x * s)) + a[10] * ((z * z * ic) + c);
    float f11 = a[3] * ((x * z * ic) + (y * s)) + a[7] * ((y * z * ic) - (x * s)) + a[11] * ((z * z * ic) + c);

    a[0] = f0; a[1] = f1; a[2] = f2; a[3] = f3;
    a[4] = f4; a[5] = f5; a[6] = f6; a[7] = f7;
    a[8] = f8; a[9] = f9; a[10] = f10; a[11] = f11;
}

void Matrix4f::rotate(const Vector3f& euler) {
    rotate(euler.x, 1, 0, 0);
    rotate(euler.y, 0, 1, 0);
    rotate(euler.z, 0, 0, 1);
}

void Matrix4f::scale(float scale) {
    a[0] *= scale;
    a[1] *= scale;
    a[2] *= scale;
    a[3] *= scale;
    a[4] *= scale;
    a[5] *= scale;
    a[6] *= scale;
    a[7] *= scale;
    a[8] *= scale;
    a[9] *= scale;
    a[10] *= scale;
    a[11] *= scale;
}

void Matrix4f::scale(const Vector3f& scale) {
    a[0] *= scale.x;
    a[1] *= scale.x;
    a[2] *= scale.x;
    a[3] *= scale.x;
    a[4] *= scale.y;
    a[5] *= scale.y;
    a[6] *= scale.y;
    a[7] *= scale.y;
    a[8] *= scale.z;
    a[9] *= scale.z;
    a[10] *= scale.z;
    a[11] *= scale.z;
}

Vector3f Matrix4f::transform(const Vector3f& v, int w) const {
    Vector3f dest;
    dest.x = a[0] * v.x + a[4] * v.y + a[8] * v.z + a[12] * w;
    dest.y = a[1] * v.x + a[5] * v.y + a[9] * v.z + a[13] * w;
    dest.z = a[2] * v.x + a[6] * v.y + a[10] * v.z + a[14] * w;
    float dest_w = a[3] * v.x + a[7] * v.y + a[11] * v.z + a[15] * w;
    return w == 0 ? dest : dest / dest_w;
}

const float* Matrix4f::toArray() const {
    return a;
}

float* Matrix4f::toArray() {
    return a;
}

std::string Matrix4f::str() const {
    std::stringstream ss;
    ss << "[" << a[0] << ", " << a[4] << ", " << a[8] << ", " << a[12] << "]\n";
    ss << "[" << a[1] << ", " << a[5] << ", " << a[9] << ", " << a[13] << "]\n";
    ss << "[" << a[2] << ", " << a[6] << ", " << a[10] << ", " << a[14] << "]\n";
    ss << "[" << a[3] << ", " << a[7] << ", " << a[11] << ", " << a[15] << "]\n";

    return ss.str();
}


/* Operator overloads */
float Matrix4f::operator[](int i) const {
    return a[i];
}

float& Matrix4f::operator[](int i) {
    return a[i];
}

bool Matrix4f::operator==(const Matrix4f& m) const {
    for (int i = 0; i < 16; i++) {
        if (a[i] != m.a[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix4f::operator!=(const Matrix4f& m) const {
    for (int i = 0; i < 16; i++) {
        if (a[i] != m.a[i]) {
            return true;
        }
    }
    return false;
}

Matrix4f Matrix4f::operator*(const Matrix4f& m) const {
    Matrix4f dest;
    dest.a[0] = a[0] * m.a[0] + a[4] * m.a[1] + a[8] * m.a[2] + a[12] * m.a[3];
    dest.a[1] = a[1] * m.a[0] + a[5] * m.a[1] + a[9] * m.a[2] + a[13] * m.a[3];
    dest.a[2] = a[2] * m.a[0] + a[6] * m.a[1] + a[10] * m.a[2] + a[14] * m.a[3];
    dest.a[3] = a[3] * m.a[0] + a[7] * m.a[1] + a[11] * m.a[2] + a[15] * m.a[3];

    dest.a[4] = a[0] * m.a[4] + a[4] * m.a[5] + a[8] * m.a[6] + a[12] * m.a[7];
    dest.a[5] = a[1] * m.a[4] + a[5] * m.a[5] + a[9] * m.a[6] + a[13] * m.a[7];
    dest.a[6] = a[2] * m.a[4] + a[6] * m.a[5] + a[10] * m.a[6] + a[14] * m.a[7];
    dest.a[7] = a[3] * m.a[4] + a[7] * m.a[5] + a[11] * m.a[6] + a[15] * m.a[7];

    dest.a[8] = a[0] * m.a[8] + a[4] * m.a[9] + a[8] * m.a[10] + a[12] * m.a[11];
    dest.a[9] = a[1] * m.a[8] + a[5] * m.a[9] + a[9] * m.a[10] + a[13] * m.a[11];
    dest.a[10] = a[2] * m.a[8] + a[6] * m.a[9] + a[10] * m.a[10] + a[14] * m.a[11];
    dest.a[11] = a[3] * m.a[8] + a[7] * m.a[9] + a[11] * m.a[10] + a[15] * m.a[11];

    dest.a[12] = a[0] * m.a[12] + a[4] * m.a[13] + a[8] * m.a[14] + a[12] * m.a[15];
    dest.a[13] = a[1] * m.a[12] + a[5] * m.a[13] + a[9] * m.a[14] + a[13] * m.a[15];
    dest.a[14] = a[2] * m.a[12] + a[6] * m.a[13] + a[10] * m.a[14] + a[14] * m.a[15];
    dest.a[15] = a[3] * m.a[12] + a[7] * m.a[13] + a[11] * m.a[14] + a[15] * m.a[15];

    return dest;
}

Vector4f Matrix4f::operator*(const Vector4f& v) const {
    Vector4f dest;
    dest.x = a[0] * v.x + a[4] * v.y + a[8] * v.z + a[12] * v.w;
    dest.y = a[1] * v.x + a[5] * v.y + a[9] * v.z + a[13] * v.w;
    dest.z = a[2] * v.x + a[6] * v.y + a[10] * v.z + a[14] * v.w;
    dest.w = a[3] * v.x + a[7] * v.y + a[11] * v.z + a[15] * v.w;
    return dest;
}

Vector3f Matrix4f::operator*(const Vector3f& v) const {
    Vector3f dest;
    dest.x = a[0] * v.x + a[4] * v.y + a[8] * v.z;
    dest.y = a[1] * v.x + a[5] * v.y + a[9] * v.z;
    dest.z = a[2] * v.x + a[6] * v.y + a[10] * v.z;
    return dest;
}

Matrix4f transpose(const Matrix4f& m) {
    Matrix4f d;
    d[0] = m[0];	d[4] = m[1];	d[8] = m[2];	d[12] = m[3];
    d[1] = m[4];	d[5] = m[5];	d[9] = m[6];	d[13] = m[7];
    d[2] = m[8];	d[6] = m[9];	d[10] = m[10];	d[14] = m[11];
    d[3] = m[12];	d[7] = m[13];	d[11] = m[14];	d[15] = m[15];
    return d;
}

float determinant(const Matrix4f& m) {
    float det =
        m[0] * m[5] * m[10] * m[15] + m[0] * m[9] * m[14] * m[7] +
        m[0] * m[13] * m[6] * m[11] + m[4] * m[1] * m[14] * m[11] +
        m[4] * m[9] * m[2] * m[15] + m[4] * m[13] * m[10] * m[3] +
        m[8] * m[1] * m[6] * m[15] + m[8] * m[5] * m[14] * m[3] +
        m[8] * m[13] * m[2] * m[7] + m[12] * m[1] * m[10] * m[7] +
        m[12] * m[5] * m[2] * m[11] + m[12] * m[9] * m[6] * m[3] -
        m[0] * m[5] * m[14] * m[11] - m[0] * m[9] * m[6] * m[15] -
        m[0] * m[13] * m[10] * m[7] - m[4] * m[1] * m[10] * m[15] -
        m[4] * m[9] * m[14] * m[3] - m[4] * m[13] * m[2] * m[11] -
        m[8] * m[1] * m[14] * m[7] - m[8] * m[5] * m[2] * m[15] -
        m[8] * m[13] * m[6] * m[3] - m[12] * m[1] * m[6] * m[11] -
        m[12] * m[5] * m[10] * m[3] - m[12] * m[9] * m[2] * m[7];

    return det;
}

Matrix4f inverse(const Matrix4f& m) {
    float det = determinant(m);

    Matrix4f d;
    d[0] = m[5] * m[10] * m[15] + m[9] * m[14] * m[7] + m[13] * m[6] * m[11]
        - m[5] * m[14] * m[11] - m[9] * m[6] * m[15] - m[13] * m[10] * m[7];
    d[1] = m[1] * m[14] * m[11] + m[9] * m[2] * m[15] + m[13] * m[10] * m[3]
        - m[1] * m[10] * m[15] - m[9] * m[14] * m[3] - m[13] * m[2] * m[11];
    d[2] = m[1] * m[6] * m[15] + m[5] * m[14] * m[3] + m[13] * m[2] * m[7]
        - m[1] * m[14] * m[7] - m[5] * m[2] * m[15] - m[13] * m[6] * m[3];
    d[3] = m[1] * m[10] * m[7] + m[5] * m[2] * m[11] + m[9] * m[6] * m[3]
        - m[1] * m[6] * m[11] - m[5] * m[10] * m[3] - m[9] * m[2] * m[7];
    d[4] = m[4] * m[14] * m[11] + m[8] * m[6] * m[15] + m[12] * m[10] * m[7]
        - m[4] * m[10] * m[15] - m[8] * m[14] * m[7] - m[12] * m[6] * m[11];
    d[5] = m[0] * m[10] * m[15] + m[8] * m[14] * m[3] + m[12] * m[2] * m[11]
        - m[0] * m[14] * m[11] - m[8] * m[2] * m[15] - m[12] * m[10] * m[3];
    d[6] = m[0] * m[14] * m[7] + m[4] * m[2] * m[15] + m[12] * m[6] * m[3]
        - m[0] * m[6] * m[15] - m[4] * m[14] * m[3] - m[12] * m[2] * m[7];
    d[7] = m[0] * m[6] * m[11] + m[4] * m[10] * m[3] + m[8] * m[2] * m[7]
        - m[0] * m[10] * m[7] - m[4] * m[2] * m[11] - m[8] * m[6] * m[3];
    d[8] = m[4] * m[9] * m[15] + m[8] * m[13] * m[7] + m[12] * m[5] * m[11]
        - m[4] * m[13] * m[11] - m[8] * m[5] * m[15] - m[12] * m[9] * m[7];
    d[9] = m[0] * m[13] * m[11] + m[8] * m[1] * m[15] + m[12] * m[9] * m[3]
        - m[0] * m[9] * m[15] - m[8] * m[13] * m[3] - m[12] * m[1] * m[11];
    d[10] = m[0] * m[5] * m[15] + m[4] * m[13] * m[3] + m[12] * m[1] * m[7]
        - m[0] * m[13] * m[7] - m[4] * m[1] * m[15] - m[12] * m[5] * m[3];
    d[11] = m[0] * m[9] * m[7] + m[4] * m[1] * m[11] + m[8] * m[5] * m[3]
        - m[0] * m[5] * m[11] - m[4] * m[9] * m[3] - m[8] * m[1] * m[7];
    d[12] = m[4] * m[13] * m[10] + m[8] * m[5] * m[14] + m[12] * m[9] * m[6]
        - m[4] * m[9] * m[14] - m[8] * m[13] * m[6] - m[12] * m[5] * m[10];
    d[13] = m[0] * m[9] * m[14] + m[8] * m[13] * m[2] + m[12] * m[1] * m[10]
        - m[0] * m[13] * m[10] - m[8] * m[1] * m[14] - m[12] * m[9] * m[2];
    d[14] = m[0] * m[13] * m[6] + m[4] * m[1] * m[14] + m[12] * m[5] * m[2]
        - m[0] * m[5] * m[14] - m[4] * m[13] * m[2] - m[12] * m[1] * m[6];
    d[15] = m[0] * m[5] * m[10] + m[4] * m[9] * m[2] + m[8] * m[1] * m[6]
        - m[0] * m[9] * m[6] - m[4] * m[1] * m[10] - m[8] * m[5] * m[2];

    d.scale(1 / det);

    return d;
}
