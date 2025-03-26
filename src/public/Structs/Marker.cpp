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
    : id(id), transform(transform), size(DEFAULT_SIZE)
{
}

Marker::Marker(int id, Transform transform, float size)
    : id(id), transform(transform), size(size)
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

float Marker::getSize() const
{
    return size;
}

void Marker::setSize(float size)
{
    this->size = size;
}

const Transform& Marker::getTransform() const
{
    return transform;
}

void Marker::setTransform(const Transform& transform)
{
    this->transform = transform;
}
