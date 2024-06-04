#pragma once
#include <ostream>
#include <iostream>
#include "Struct/Vec3.hpp"
#include "Struct/Quaternion.hpp"
#include "Struct/Nullable.hpp"

class Pose: public Nullable
{
protected:
    Vec3f position;
    Quaternion rotation;

public:
    Pose(): position(Vec3f()), rotation(Quaternion()) {}
    Pose(const Vec3f& position, const Quaternion& rotation): position(position), rotation(rotation) {}
    Pose(const Pose& other): Nullable(other), position(other.position), rotation(other.rotation) {}
    ~Pose() {}

    Vec3f getPosition() const { return position; }
    Quaternion getRotation() const { return rotation; }

    friend std::ostream& operator<<(std::ostream& os, const Pose& pose)
    {
        os << "Pose(position=" << pose.position << ", rotation=" << pose.rotation << ")";
        return os;
    }
};
