#include "Struct/Pose.hpp"

Pose::Pose()
    : position(Vec3f()), rotation(Quaternion())
{

}

Pose::Pose(const Vec3f& position, const Quaternion& rotation)
    : position(position), rotation(rotation)
{

}

Pose::Pose(const Pose& pose)
    : position(pose.position), rotation(pose.rotation)
{

}

Pose::~Pose()
{

}

const Vec3f& Pose::getPosition() const
{
    return position;
}

const Quaternion& Pose::getRotation() const
{
    return rotation;
}
