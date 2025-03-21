#include <Identifiable.hpp>
#include <Structs/Skeleton.hpp>
#include <Structs/Joint.hpp>

Skeleton::Skeleton()
{
}

Skeleton::~Skeleton()
{
}

std::ostream& operator<<(std::ostream& os, const Skeleton& skeleton)
{
    os << "Skeleton(" << skeleton.getID() << ")";
    return os;
}

const std::array<Joint, Skeleton::NB_JOINTS>& Skeleton::getJoints() const
{
    return m_joints;
}

const Joint& Skeleton::getJoint(int id) const
{
    return m_joints.at(id);
}

const size_t Skeleton::getJointCount() const
{
    return Skeleton::NB_JOINTS;
}

void Skeleton::setJoint(int id, const Joint& joint)
{
    m_joints[id] = joint;
}
