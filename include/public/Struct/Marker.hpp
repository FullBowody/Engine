#pragma once
#include "Struct/Pose.hpp"
#include "Struct/Nullable.hpp"

class Marker: public Nullable
{
private:
    Pose pose;
    int id;

public:
    Marker(): pose(), id(0) {}
    Marker(const Pose& pose, int id): pose(pose), id(id) {}
    Marker(const Marker& marker): pose(marker.pose), id(marker.id) {}
    ~Marker() {}

    const Pose& getPose() const
    {
        return pose;
    }

    void setPose(const Pose& pose)
    {
        this->pose = pose;
    }

    int getId() const
    {
        return id;
    }
};
