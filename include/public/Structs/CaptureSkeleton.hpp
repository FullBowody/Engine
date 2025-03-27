#pragma once
#include <array>
#include <ostream>
#include "Structs/CaptureJoint.hpp"
#include "Structs/Skeleton.hpp"
#include "utils.hpp"

class ENGINE_API CaptureSkeleton
{
private:
    std::array<std::shared_ptr<CaptureJoint>, Skeleton::NB_JOINTS> joints;

public:
    CaptureSkeleton();
    virtual ~CaptureSkeleton();

    friend std::ostream& operator<<(std::ostream& os, const CaptureSkeleton& skeleton);

    virtual void setJoint(int id, const CaptureJoint& joint);
    virtual const std::array<std::shared_ptr<CaptureJoint>, Skeleton::NB_JOINTS>& getJoints() const;
    virtual std::shared_ptr<CaptureJoint> getJoint(int id) const;
    virtual const size_t getJointCount() const;
};
