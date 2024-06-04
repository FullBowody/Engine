#pragma once
#include <math.h>
#include "Vec3.hpp"

class Quaternion: public Nullable
{
public:
    static Quaternion Euler(float x, float y, float z)
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

    static Quaternion FromRotationMatrix(float* m)
    {
        float t = m[0] + m[4] + m[8];
        float s, x, y, z, w;

        if (t > 0)
        {
            s = 0.5f / sqrt(t + 1);
            w = 0.25f / s;
            x = (m[7] - m[5]) * s;
            y = (m[2] - m[6]) * s;
            z = (m[3] - m[1]) * s;
        }
        else if (m[0] > m[4] && m[0] > m[8])
        {
            s = 2 * sqrt(1 + m[0] - m[4] - m[8]);
            w = (m[7] - m[5]) / s;
            x = 0.25f * s;
            y = (m[1] + m[3]) / s;
            z = (m[2] + m[6]) / s;
        }
        else if (m[4] > m[8])
        {
            s = 2 * sqrt(1 + m[4] - m[0] - m[8]);
            w = (m[2] - m[6]) / s;
            x = (m[1] + m[3]) / s;
            y = 0.25f * s;
            z = (m[5] + m[7]) / s;
        }
        else
        {
            s = 2 * sqrt(1 + m[8] - m[0] - m[4]);
            w = (m[3] - m[1]) / s;
            x = (m[2] + m[6]) / s;
            y = (m[5] + m[7]) / s;
            z = 0.25f * s;
        }

        return Quaternion(x, y, z, w);
    }

    float x, y, z, w;

    Quaternion() : x(0), y(0), z(0), w(1) {}
    Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Quaternion(const Quaternion& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
    ~Quaternion() {}

    Quaternion normalize() const
    {
        return *this * (1.0f / sqrt(x*x + y*y + z*z + w*w));
    }

    Quaternion inverse() const
    {
        return conjugate() * (1.0f / (x*x + y*y + z*z + w*w));
    }

    Quaternion conjugate() const
    {
        return Quaternion(-x, -y, -z, w);
    }

    float dot(const Quaternion& q) const
    {
        return x*q.x + y*q.y + z*q.z + w*q.w;
    }

    float length() const
    {
        return sqrt(x*x + y*y + z*z + w*w);
    }

    
    Quaternion operator*(const Quaternion& q) const
    {
        return Quaternion(
            w*q.x + x*q.w + y*q.z - z*q.y,
            w*q.y - x*q.z + y*q.w + z*q.x,
            w*q.z + x*q.y - y*q.x + z*q.w,
            w*q.w - x*q.x - y*q.y - z*q.z
        );
    }

    Quaternion operator*(float s) const
    {
        return Quaternion(x*s, y*s, z*s, w*s);
    }

    Vec3f operator*(const Vec3f& v) const
    {
        Quaternion p(v.x, v.y, v.z, 0);
        Quaternion q = *this * p * conjugate();
        return Vec3f(q.x, q.y, q.z);
    }

    Quaternion operator+(const Quaternion& q) const
    {
        return Quaternion(x+q.x, y+q.y, z+q.z, w+q.w);
    }

    Quaternion operator-(const Quaternion& q) const
    {
        return Quaternion(x-q.x, y-q.y, z-q.z, w-q.w);
    }

    Quaternion operator-() const
    {
        return Quaternion(-x, -y, -z, -w);
    }

    Quaternion operator/(float s) const
    {
        return Quaternion(x/s, y/s, z/s, w/s);
    }

    Quaternion operator*= (const Quaternion& q)
    {
        return *this = *this * q;
    }

    Quaternion operator*= (float s)
    {
        return *this = *this * s;
    }

    Quaternion operator/= (float s)
    {
        return *this = *this / s;
    }

    Quaternion operator+= (const Quaternion& q)
    {
        return *this = *this + q;
    }

    Quaternion operator-= (const Quaternion& q)
    {
        return *this = *this - q;
    }
};
