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
    if (id >= 0 && id < joints.size())
    {
        joints[id] = std::make_shared<CaptureJoint>(joint);
    }
}

const std::array<std::shared_ptr<CaptureJoint>, Skeleton::NB_JOINTS>& CaptureSkeleton::getJoints() const
{
    return joints;
}

std::shared_ptr<CaptureJoint> CaptureSkeleton::getJoint(int id) const
{
    return joints.at(id);
}

const size_t CaptureSkeleton::getJointCount() const
{
    return Skeleton::NB_JOINTS;
}
