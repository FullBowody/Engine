#pragma once
#include <iostream>
#include "Struct/Nullable.hpp"

template <typename T>
class Vec2: public Nullable
{
public:
    T x, y;

    Vec2();
    Vec2(T x, T y);
    Vec2(const Vec2 &other);
    ~Vec2();

    T dot(const Vec2 &other) const { return x * other.x + y * other.y; }
    T length() const { return sqrt(x * x + y * y); }
    Vec2 normalize() const { return *this / length(); }

    Vec2 &operator=(const Vec2 &other);
    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &other) const;
    Vec2 operator+=(const Vec2 &other) { return *this = *this + other; }
    Vec2 operator-=(const Vec2 &other) { return *this = *this - other; }
    Vec2 operator*(T scalar) const { return Vec2(x * scalar, y * scalar); }
    Vec2 operator/(T scalar) const { return Vec2(x / scalar, y / scalar); }
    Vec2 operator*=(T scalar) { return *this = *this * scalar; }
    Vec2 operator/=(T scalar) { return *this = *this / scalar; }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& dt)
    {
        os << "Vec2(x=" << dt.x << ", y=" << dt.y << ")";
        return os;
    }
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;

template <typename T>
Vec2<T>::Vec2() : x(0), y(0) {}

template <typename T>
Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}

template <typename T>
Vec2<T>::Vec2(const Vec2 &other) : x(other.x), y(other.y) {}

template <typename T>
Vec2<T>::~Vec2() {}

template <typename T>
Vec2<T> &Vec2<T>::operator=(const Vec2 &other)
{
    x = other.x;
    y = other.y;
    return *this;
}

template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2 &other) const
{
    return Vec2(x + other.x, y + other.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2 &other) const
{
    return Vec2(x - other.x, y - other.y);
}
