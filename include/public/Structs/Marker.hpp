#pragma once
#include "Structs/Transform.hpp"
#include "utils.hpp"

class ENGINE_API Marker
{
public:
    inline static const float DEFAULT_SIZE = 0.25f; // meters

    Marker();
    Marker(int id);
    Marker(int id, Transform transform);
    Marker(int id, Transform transform, float size);
    virtual ~Marker();

    virtual int getId() const;
    virtual void setId(int id);
    virtual const Transform& getTransform() const;
    virtual void setTransform(const Transform& transform);
    virtual float getSize() const;
    virtual void setSize(float size);

private:
    int id;
    float size;
    Transform transform;
};
