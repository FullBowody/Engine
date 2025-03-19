#include <Structs/Skeleton.hpp>

Skeleton::Skeleton() : m_joints(NB_JOINTS)
{
    // Empty constructor
}

Skeleton::Skeleton(const std::vector<Transform>& m_joints) : m_joints(m_joints)
{
    // Empty constructor with m_joints initialization
}

Skeleton::Skeleton(const Skeleton& other) : m_joints(other.m_joints)
{
    // Copy constructor
}

Skeleton::~Skeleton()
{
    // Destructor
}

Skeleton& Skeleton::operator=(const Skeleton& other)
{
    if (this != &other) {
        m_joints = other.m_joints;
    }
    return *this;
}

bool Skeleton::operator==(const Skeleton& other) const
{
    return m_joints == other.m_joints;
}

bool Skeleton::operator!=(const Skeleton& other) const
{
    return m_joints != other.m_joints;
}

std::ostream& operator<<(std::ostream& os, const Skeleton& skeleton)
{
    os << "Skeleton(m_joints=" << skeleton.m_joints << ")";
    return os;
}

const std::vector<Transform>& Skeleton::getJoints() const
{
    return m_joints;
}

const Transform& Skeleton::getJoint(int joint) const
{
    return m_joints.at(joint);
}

const size_t Skeleton::getNbJoints() const
{
    return NB_JOINTS;
}

void Skeleton::setJoint(int joint, const Transform& transform)
{
    if (joint >= 0 && joint < m_joints.size()) {
        m_joints[joint] = transform;
    }
}

void Skeleton::setJoints(const std::vector<Transform>& m_joints)
{
    this->m_joints = m_joints;
}