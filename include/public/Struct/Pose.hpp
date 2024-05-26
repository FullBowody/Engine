#pragma once
#include "Struct/Vec3.hpp"
#include "Struct/Quaternion.hpp"

class Pose
{
protected:
    Vec3f position;
    Quaternion rotation;

public:
    Pose();
    Pose(const Vec3f& position, const Quaternion& rotation);
    Pose(const Pose& pose);
    ~Pose();

    const Vec3f& getPosition() const;
    const Quaternion& getRotation() const;
};
