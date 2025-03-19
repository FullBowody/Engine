#pragma once
#include <vector>
#include <ostream>
#include "Structs/CaptureJoint.hpp"
#include "utils.hpp"

class DLLExport CaptureSkeleton
{
private:
    std::vector<CaptureJoint> joints;

public:
    CaptureSkeleton();
    CaptureSkeleton(const std::vector<CaptureJoint>& joints);
    CaptureSkeleton(const CaptureSkeleton& skeleton);
    virtual ~CaptureSkeleton();

    CaptureSkeleton& operator=(const CaptureSkeleton& other);
    bool operator==(const CaptureSkeleton& other) const;
    bool operator!=(const CaptureSkeleton& other) const;
    friend std::ostream& operator<<(std::ostream& os, const CaptureSkeleton& skeleton);

    void setJoints(const std::vector<CaptureJoint>& joints);
    void setJoint(int id, const CaptureJoint& joint);
    std::vector<CaptureJoint> getJoints() const;
    CaptureJoint getJoint(int id) const;
    int getJointCount() const;
};

CaptureSkeleton::CaptureSkeleton()
{
}

CaptureSkeleton::CaptureSkeleton(const std::vector<CaptureJoint>& joints)
{
    this->joints = joints;
}

CaptureSkeleton::CaptureSkeleton(const CaptureSkeleton& skeleton)
{
    this->joints = skeleton.joints;
}

CaptureSkeleton::~CaptureSkeleton()
{
}

CaptureSkeleton& CaptureSkeleton::operator=(const CaptureSkeleton& other)
{
    if (this != &other)
    {
        this->joints = other.joints;
    }
    return *this;
}

bool CaptureSkeleton::operator==(const CaptureSkeleton& other) const
{
    return this->joints == other.joints;
}

bool CaptureSkeleton::operator!=(const CaptureSkeleton& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CaptureSkeleton& skeleton)
{
    os << "CaptureSkeleton(joints=" << skeleton.joints << ")";
    return os;
}

void CaptureSkeleton::setJoints(const std::vector<CaptureJoint>& joints)
{
    this->joints = joints;
}

void CaptureSkeleton::setJoint(int id, const CaptureJoint& joint)
{
    if (id >= 0 && id < joints.size())
    {
        joints[id] = joint;
    }
}

std::vector<CaptureJoint> CaptureSkeleton::getJoints() const
{
    return joints;
}

CaptureJoint CaptureSkeleton::getJoint(int id) const
{
    if (id >= 0 && id < joints.size())
    {
        return joints[id];
    }
    return CaptureJoint();
}

int CaptureSkeleton::getJointCount() const
{
    return joints.size();
}

