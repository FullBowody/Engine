#pragma once
#include <iostream>
#include "utils.hpp"
#include "Struct/Nullable.hpp"

template <typename T>
class Vec3: public Nullable
{
public:
    T x, y, z;

    Vec3();
    Vec3(T x, T y, T z);
    Vec3(const Vec3 &other);
    ~Vec3();

    T dot(const Vec3 &other) const { return x * other.x + y * other.y + z * other.z; }
    Vec3 cross(const Vec3 &other) const { return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
    T length() const { return sqrt(x * x + y * y + z * z); }
    Vec3 normalize() const { return *this / length(); }

    Vec3 &operator=(const Vec3 &other);
    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator+=(const Vec3 &other) { return *this = *this + other; }
    Vec3 operator-=(const Vec3 &other) { return *this = *this - other; }
    Vec3 operator-() const { return Vec3(-x, -y, -z); }
    Vec3 operator*(T scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
    Vec3 operator/(T scalar) const { return Vec3(x / scalar, y / scalar, z / scalar); }
    Vec3 operator*=(T scalar) { return *this = *this * scalar; }
    Vec3 operator/=(T scalar) { return *this = *this / scalar; }
    friend std::ostream& operator<<(std::ostream& os, const Vec3& dt)
    {
        os << "(" << dt.x << ", " << dt.y << ", " << dt.z << ")";
        return os;
    }
};

typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

template <typename T>
Vec3<T>::Vec3() : x(0), y(0), z(0) {}

template <typename T>
Vec3<T>::Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

template <typename T>
Vec3<T>::Vec3(const Vec3 &other) : x(other.x), y(other.y), z(other.z) {}

template <typename T>
Vec3<T>::~Vec3() {}

template <typename T>
Vec3<T> &Vec3<T>::operator=(const Vec3 &other)
{
    x = other.x;
    y = other.y;
    return *this;
}

template <typename T>
Vec3<T> Vec3<T>::operator+(const Vec3 &other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

template <typename T>
Vec3<T> Vec3<T>::operator-(const Vec3 &other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}
