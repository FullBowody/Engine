#include "Structs/Joint.hpp"

Joint::Joint()
{
}

Joint::~Joint()
{
}

std::ostream& operator<<(std::ostream& os, const Joint& joint)
{
    os << "Joint(" << joint.getTransform() << ")";
    return os;
}

const Transform& Joint::getTransform() const
{
    return transform;
}

void Joint::setTransform(const Transform& transform)
{
    this->transform = transform;
}
