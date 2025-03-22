#pragma once
#include <array>
#include <optional>
#include "Structs/Joint.hpp"
#include "Identifiable.hpp"
#include "utils.hpp"

class ENGINE_API Skeleton : public Identifiable
{
public:
    static const int JOINT_HIP = 0;
    static const int JOINT_SPINE = 1;
    static const int JOINT_CHEST = 2;
    static const int JOINT_NECK = 3;
    static const int JOINT_HEAD = 4;
    static const int JOINT_SHOULDER_L = 5;
    static const int JOINT_SHOULDER_R = 6;
    static const int JOINT_ELBOW_L = 7;
    static const int JOINT_ELBOW_R = 8;
    static const int JOINT_WRIST_L = 9;
    static const int JOINT_WRIST_R = 10;
    static const int JOINT_HAND_L = 11;
    static const int JOINT_HAND_R = 12;
    static const int JOINT_HIP_L = 13;
    static const int JOINT_HIP_R = 14;
    static const int JOINT_KNEE_L = 15;
    static const int JOINT_KNEE_R = 16;
    static const int JOINT_ANKLE_L = 17;
    static const int JOINT_ANKLE_R = 18;
    static const int NB_JOINTS = 19;

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
