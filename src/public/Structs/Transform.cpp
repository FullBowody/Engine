#include "Structs/Transform.hpp"

void Transform::calculateGlobalPositionRotation()
{
    if (!parent)
    {
        global_position = position;
        global_rotation = rotation;
    }
    else
    {
        global_position = parent->getGlobalPosition() + parent->getGlobalRotation() * position;
        global_rotation = parent->getGlobalRotation() * rotation;
    }
    outdated = false;
}

void Transform::markOutdatedRecursive()
{
    outdated = true;
    for (auto& child : children)
    {
        child->markOutdatedRecursive();
    }
}

void Transform::addChild(Transform* child)
{
    children.push_back(child);
}

void Transform::removeChild(Transform* child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

Transform::Transform()
{
}

Transform::Transform(const std::string& name)
    : name(name)
{
}

Transform::Transform(const std::string& name, const glm::vec3& position, const glm::quat& rotation)
    : name(name), position(position), rotation(rotation), outdated(true)
{
}

Transform::~Transform()
{
    if (parent)
    {
        parent->removeChild(this);
    }
}

std::ostream& operator<<(std::ostream& os, const Transform& transform)
{
    os << "Transform(" << transform.name << ")";
    return os;
}

void Transform::setParent(std::shared_ptr<Transform> parent)
{
    if (parent)
    {
        parent->removeChild(this);
    }
    parent = parent;
    if (parent)
    {
        parent->addChild(this);
    }
    markOutdatedRecursive();
}

std::shared_ptr<Transform> Transform::getParent() const
{
    return parent;
}

void Transform::setLocalPosition(const glm::vec3& position)
{
    this->position = position;
    markOutdatedRecursive();
}

glm::vec3 Transform::getLocalPosition() const
{
    return position;
}

void Transform::setLocalRotation(const glm::quat& rotation)
{
    this->rotation = rotation;
    markOutdatedRecursive();
}

glm::quat Transform::getLocalRotation() const
{
    return rotation;
}

glm::vec3 Transform::getGlobalPosition()
{
    if (outdated)
    {
        calculateGlobalPositionRotation();
    }

    return global_position;
}

glm::vec3 Transform::getGlobalPosition(Transform& root)
{
    glm::vec3 root_position = root.getGlobalPosition();
    glm::quat root_rotation = root.getGlobalRotation();

    glm::vec3 own_position = getGlobalPosition();
    glm::quat own_rotation = getGlobalRotation();

    return root_rotation * (own_position - root_position);
}

glm::quat Transform::getGlobalRotation()
{
    if (outdated)
    {
        calculateGlobalPositionRotation();
    }

    return global_rotation;
}

glm::quat Transform::getGlobalRotation(Transform& root)
{
    glm::vec3 root_position = root.getGlobalPosition();
    glm::quat root_rotation = root.getGlobalRotation();

    glm::vec3 own_position = getGlobalPosition();
    glm::quat own_rotation = getGlobalRotation();

    return glm::inverse(root_rotation) * own_rotation;
}
