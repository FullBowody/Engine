#pragma once
#include "Vec3.hpp"

class DLLExport Quaternion: public Nullable
{
public:
    static Quaternion Euler(float x, float y, float z);
    static Quaternion Euler(const Vec3f& vec);
    static Quaternion FromRotationMatrix(float* m);

    float x, y, z, w;

    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(const Quaternion& other);
    ~Quaternion();

    Quaternion normalize() const;
    Quaternion inverse() const;
    Quaternion conjugate() const;
    float dot(const Quaternion& q) const;
    float length() const;
    
    Quaternion operator*(const Quaternion& q) const;
    Quaternion operator*(float s) const;
    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator-(const Quaternion& q) const;
    Quaternion operator-() const;
    Quaternion operator/(float s) const;
    Quaternion operator*= (const Quaternion& q);
    Quaternion operator*= (float s);
    Quaternion operator/= (float s);
    Quaternion operator+= (const Quaternion& q);
    Quaternion operator-= (const Quaternion& q);

    Vec3f operator*(const Vec3f& v) const;
};
