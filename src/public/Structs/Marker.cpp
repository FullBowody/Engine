#include "Structs/Marker.hpp"
#include "Structs/Transform.hpp"

Marker::Marker()
    : id(-1)
{
}

Marker::Marker(int id)
    : id(id)
{
}

Marker::Marker(int id, Transform transform)
    : id(id), transform(transform)
{
}

Marker::~Marker()
{
}

int Marker::getId() const
{
    return id;
}

void Marker::setId(int id)
{
    this->id = id;
}

const Transform& Marker::getTransform() const
{
    return transform;
}

void Marker::setTransform(const Transform& transform)
{
    this->transform = transform;
}
