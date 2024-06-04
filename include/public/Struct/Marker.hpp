#pragma once
#include <ostream>
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
    Marker(const Marker& other): Nullable(other), pose(other.pose), id(other.id) {}
    ~Marker() {}

    const Pose& getPose() const { return pose; }
    void setPose(const Pose& pose) { this->pose = pose; }
    int getId() const { return id; }

    friend std::ostream& operator<<(std::ostream& os, const Marker& marker)
    {
        os << "Marker(id=" << marker.id << ", pose=" << marker.pose << ")";
        return os;
    }
};
