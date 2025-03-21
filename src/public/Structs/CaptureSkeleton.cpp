#include "Structs/CaptureSkeleton.hpp"

CaptureSkeleton::CaptureSkeleton()
{
}

CaptureSkeleton::~CaptureSkeleton()
{
}

std::ostream& operator<<(std::ostream& os, const CaptureSkeleton& skeleton)
{
    os << "CaptureSkeleton()";
    return os;
}

void CaptureSkeleton::setJoint(int id, const CaptureJoint& joint)
{
    if (id >= 0 && id < m_joints.size())
    {
        m_joints[id] = joint;
    }
}

const std::array<CaptureJoint, Skeleton::NB_JOINTS>& CaptureSkeleton::getJoints() const
{
    return m_joints;
}

const CaptureJoint& CaptureSkeleton::getJoint(int id) const
{
    return m_joints.at(id);
}

const size_t CaptureSkeleton::getJointCount() const
{
    return Skeleton::NB_JOINTS;
}
