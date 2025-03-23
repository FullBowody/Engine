#pragma once
#include <array>
#include <optional>
#include "Structs/Joint.hpp"
#include "Identifiable.hpp"
#include "utils.hpp"

class ENGINE_API Skeleton : public Identifiable
{
public:
    enum SkeletonJoint {
        JOINT_HIP = 0,
        JOINT_SPINE = 1,
        JOINT_CHEST = 2,
        JOINT_NECK = 3,
        JOINT_HEAD = 4,
        JOINT_SHOULDER_L = 5,
        JOINT_SHOULDER_R = 6,
        JOINT_ELBOW_L = 7,
        JOINT_ELBOW_R = 8,
        JOINT_WRIST_L = 9,
        JOINT_WRIST_R = 10,
        JOINT_HAND_L = 11,
        JOINT_HAND_R = 12,
        JOINT_HIP_L = 13,
        JOINT_HIP_R = 14,
        JOINT_KNEE_L = 15,
        JOINT_KNEE_R = 16,
        JOINT_ANKLE_L = 17,
        JOINT_ANKLE_R = 18,
        NB_JOINTS = 19
    };

private:
    std::array<Joint, NB_JOINTS> joints;

public:
    Skeleton();
    virtual ~Skeleton();

    friend std::ostream& operator<<(std::ostream& os, const Skeleton& skeleton);

    virtual const std::array<Joint, NB_JOINTS>& getJoints() const;
    virtual const Joint& getJoint(int id) const;
    virtual const size_t getJointCount() const;

    virtual void setJoint(int id, const Joint& joint);
};
