#pragma once
#include <ostream>
#include "Struct/Pose.hpp"
#include "Struct/Nullable.hpp"

class Marker: public Nullable
{
private:
    int id;
    Pose pose;

public:
    Marker(): id(0), pose() {}
    Marker(int id, const Pose& pose): id(id), pose(pose) {}
    Marker(const Marker& other): Nullable(other), id(other.id), pose(other.pose) {}
    ~Marker() {}

    int getId() const { return id; }
    const Pose& getPose() const { return pose; }
    void setId(int id) { this->id = id; }
    void setPose(const Pose& pose) { this->pose = pose; }

    friend std::ostream& operator<<(std::ostream& os, const Marker& marker)
    {
        os << "Marker(id=" << marker.id << ", pose=" << marker.pose << ")";
        return os;
    }
};
