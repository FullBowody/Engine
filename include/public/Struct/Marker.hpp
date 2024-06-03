#pragma once
#include "Struct/Pose.hpp"
#include "Struct/Nullable.hpp"

class Marker: public Nullable
{
private:
    Pose pose;
    int id;

public:
    Marker();
    Marker(const Pose& pose, int id);
    Marker(const Marker& marker);
    ~Marker();

    const Pose& getPose() const;
    void setPose(const Pose& pose);
    int getId() const;
};
