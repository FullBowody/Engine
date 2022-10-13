#pragma once
#include <vector>
#include "../common/common.hpp"

namespace Joint
{
    const unsigned char JOINT_COUNT = 14;

    const unsigned char JOINT_UNKNOWN = 0;

    const unsigned char JOINT_SHOULDER_R = 1;
    const unsigned char JOINT_ELBOW_R = 2;
    const unsigned char JOINT_HAND_R = 3;
    const unsigned char JOINT_HIP_R = 4;
    const unsigned char JOINT_KNEE_R = 5;
    const unsigned char JOINT_FEET_R = 6;

    const unsigned char JOINT_SHOULDER_L = 7;
    const unsigned char JOINT_ELBOW_L = 8;
    const unsigned char JOINT_HAND_L = 9;
    const unsigned char JOINT_HIP_L = 10;
    const unsigned char JOINT_KNEE_L = 11;
    const unsigned char JOINT_FEET_L = 12;

    const unsigned char JOINT_HEAD = 13;
    const unsigned char JOINT_NECK = 14;
    
    const unsigned char JOINT_LINK_COUNT = 13;
    const unsigned char JOINT_LINKS[JOINT_LINK_COUNT][2] = {
        {JOINT_HEAD, JOINT_NECK},
        {JOINT_NECK, JOINT_SHOULDER_R},
        {JOINT_NECK, JOINT_SHOULDER_L},
        {JOINT_SHOULDER_R, JOINT_ELBOW_R},
        {JOINT_SHOULDER_L, JOINT_ELBOW_L},
        {JOINT_ELBOW_R, JOINT_HAND_R},
        {JOINT_ELBOW_L, JOINT_HAND_L},
        {JOINT_NECK, JOINT_HIP_R},
        {JOINT_NECK, JOINT_HIP_L},
        {JOINT_HIP_R, JOINT_KNEE_R},
        {JOINT_HIP_L, JOINT_KNEE_L},
        {JOINT_KNEE_R, JOINT_FEET_R},
        {JOINT_KNEE_L, JOINT_FEET_L}
    };
}

class BodyJoint
{
private:
    Position position;
    Rotation rotation;
    unsigned char confidence;

public:
    BodyJoint();
    BodyJoint(Position position, Rotation rotation, unsigned char confidence);
    ~BodyJoint();

    void setPosition(Position position);
    void setRotation(Rotation rotation);
    void setConfidence(unsigned char confidence);

    Position getPosition();
    Rotation getRotation();
    unsigned char getConfidence();

    bool fromBuffer(std::vector<unsigned char> buff);
    bool fromBuffer(std::vector<unsigned char> buff, unsigned int offset);
    std::vector<unsigned char> toBuffer();
};