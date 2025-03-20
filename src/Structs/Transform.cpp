#include "Structs/Transform.hpp"

void Transform::calculateGlobalPositionRotation()
{
    if (m_parent == nullptr)
    {
        m_global_position = m_position;
        m_global_rotation = m_rotation;
    }
    else
    {
        m_global_position = m_parent->getGlobalPosition() + m_parent->getGlobalRotation() * m_position;
        m_global_rotation = m_parent->getGlobalRotation() * m_rotation;
    }
    m_outdated = false;
}

void Transform::markOutdatedRecursive()
{
    m_outdated = true;
    for (Transform& child : m_children)
    {
        child.markOutdatedRecursive();
    }
}

void Transform::addChild(Transform& child)
{
    m_children.push_back(child);
    child.setParent(this);
}

void Transform::removeChild(Transform& child)
{
    m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
    child.setParent(nullptr);
}

Transform::Transform()
{
}

Transform::Transform(const std::string& name)
    : m_name(name)
{
}

Transform::Transform(const std::string& name, const glm::vec3& position, const glm::quat& rotation)
    : m_name(name), m_position(position), m_rotation(rotation), m_outdated(true)
{
}

Transform::Transform(const Transform& other)
    : m_name(other.m_name), m_position(other.m_position), m_rotation(other.m_rotation),
      m_parent(other.m_parent), m_children(other.m_children), m_outdated(other.m_outdated),
      m_global_position(other.m_global_position), m_global_rotation(other.m_global_rotation)
{
}

Transform::~Transform()
{
    for (Transform& child : m_children)
    {
        child.setParent(m_parent);
    }
}

void Transform::setParent(Transform* parent)
{
    if (m_parent != nullptr)
    {
        m_parent->removeChild(*this);
    }
    m_parent = parent;
    if (m_parent != nullptr)
    {
        m_parent->addChild(*this);
    }
    markOutdatedRecursive();
}

Transform* Transform::getParent() const
{
    return m_parent;
}

void Transform::setLocalPosition(const glm::vec3& position)
{
    m_position = position;
    markOutdatedRecursive();
}

glm::vec3 Transform::getLocalPosition() const
{
    return m_position;
}

void Transform::setLocalRotation(const glm::quat& rotation)
{
    m_rotation = rotation;
    markOutdatedRecursive();
}

glm::quat Transform::getLocalRotation() const
{
    return m_rotation;
}

glm::vec3 Transform::getGlobalPosition()
{
    if (m_outdated)
    {
        calculateGlobalPositionRotation();
    }

    return m_global_position;
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
    if (m_outdated)
    {
        calculateGlobalPositionRotation();
    }

    return m_global_rotation;
}

glm::quat Transform::getGlobalRotation(Transform& root)
{
    glm::vec3 root_position = root.getGlobalPosition();
    glm::quat root_rotation = root.getGlobalRotation();

    glm::vec3 own_position = getGlobalPosition();
    glm::quat own_rotation = getGlobalRotation();

    return glm::inverse(root_rotation) * own_rotation;
}
