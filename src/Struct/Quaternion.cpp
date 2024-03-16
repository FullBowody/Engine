#include "Struct/Quaternion.hpp"
#include <math.h>

Quaternion Quaternion::Euler(float x, float y, float z)
{
    float cx = cos(x/2);
    float sx = sin(x/2);
    float cy = cos(y/2);
    float sy = sin(y/2);
    float cz = cos(z/2);
    float sz = sin(z/2);

    return Quaternion(
        sx*cy*cz + cx*sy*sz,
        cx*sy*cz - sx*cy*sz,
        cx*cy*sz + sx*sy*cz,
        cx*cy*cz - sx*sy*sz
    );
}

Quaternion::Quaternion()
    : x(0), y(0), z(0), w(1) {}

Quaternion::Quaternion(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w) {}

Quaternion::Quaternion(const Quaternion& other)
    : x(other.x), y(other.y), z(other.z), w(other.w) {}

Quaternion::~Quaternion() {}

Quaternion Quaternion::normalize() const
{
    return *this * (1.0f / sqrt(x*x + y*y + z*z + w*w));
}

Quaternion Quaternion::inverse() const
{
    return conjugate() * (1.0f / (x*x + y*y + z*z + w*w));
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
    return Quaternion(
        w*q.x + x*q.w + y*q.z - z*q.y,
        w*q.y - x*q.z + y*q.w + z*q.x,
        w*q.z + x*q.y - y*q.x + z*q.w,
        w*q.w - x*q.x - y*q.y - z*q.z
    );
}

Quaternion Quaternion::operator*(float s) const
{
    return Quaternion(x*s, y*s, z*s, w*s);
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
    return Quaternion(x+q.x, y+q.y, z+q.z, w+q.w);
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
    return Quaternion(x-q.x, y-q.y, z-q.z, w-q.w);
}

Quaternion Quaternion::operator-() const
{
    return Quaternion(-x, -y, -z, -w);
}

Vec3f Quaternion::operator*(const Vec3f& v) const
{
    Quaternion p(v.x, v.y, v.z, 0);
    Quaternion q = *this * p * conjugate();
    return Vec3f(q.x, q.y, q.z);
}
