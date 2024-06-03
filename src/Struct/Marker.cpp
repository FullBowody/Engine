#include "Struct/Marker.hpp"

Marker::Marker()
    : pose(), id(0)
{
}

Marker::Marker(const Pose& pose, int id)
    : pose(pose), id(id)
{
}

Marker::Marker(const Marker& marker)
    : pose(marker.pose), id(marker.id)
{
}

Marker::~Marker()
{
}

const Pose& Marker::getPose() const
{
    return pose;
}

void Marker::setPose(const Pose& pose)
{
    this->pose = pose;
}

int Marker::getId() const
{
    return id;
}
