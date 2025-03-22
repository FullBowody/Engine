#pragma once
#include <array>
#include <ostream>
#include "Structs/CaptureJoint.hpp"
#include "Structs/Skeleton.hpp"
#include "utils.hpp"

class ENGINE_API CaptureSkeleton
{
private:
    std::array<CaptureJoint, Skeleton::NB_JOINTS> joints;

public:
    CaptureSkeleton();
    virtual ~CaptureSkeleton();

    friend std::ostream& operator<<(std::ostream& os, const CaptureSkeleton& skeleton);

    void setJoint(int id, const CaptureJoint& joint);
    const std::array<CaptureJoint, Skeleton::NB_JOINTS>& getJoints() const;
    const CaptureJoint& getJoint(int id) const;
    const size_t getJointCount() const;
};
