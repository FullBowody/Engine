#pragma once
#include "Structs/Transform.hpp"

class Marker
{
private:
    int id;
    Transform transform;

public:
    Marker();
    Marker(int id);
    Marker(int id, Transform transform);
    virtual ~Marker();

    int getId() const;
    const Transform& getTransform() const;
    void setTransform(const Transform& transform);
};
