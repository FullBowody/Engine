#pragma once
#include "Structs/Transform.hpp"
#include "utils.hpp"

class ENGINE_API Marker
{
private:
    int id;
    Transform transform;

public:
    Marker();
    Marker(int id);
    Marker(int id, Transform transform);
    virtual ~Marker();

    virtual int getId() const;
    virtual void setId(int id);
    virtual const Transform& getTransform() const;
    virtual void setTransform(const Transform& transform);
};
