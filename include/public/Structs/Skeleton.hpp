#pragma once
#include <vector>
#include "Structs/Transform.hpp"
#include "utils.hpp"

class DLLExport Skeleton
{
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

public:
    std::vector<Transform> m_joints;

    Skeleton();
    Skeleton(const std::vector<Transform>& joints);
    Skeleton(const Skeleton& other);
    ~Skeleton();

    Skeleton& operator=(const Skeleton& other);
    bool operator==(const Skeleton& other) const;
    bool operator!=(const Skeleton& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Skeleton& skeleton);

    const std::vector<Transform>& getJoints() const;
    const Transform& getJoint(int joint) const;
    const size_t getNbJoints() const;

    void setJoint(int joint, const Transform& transform);
    void setJoints(const std::vector<Transform>& joints);
};
