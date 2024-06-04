#pragma once
#include <memory.h>
#include "Struct/Vec2.hpp"
#include "Struct/Vec3.hpp"
#include "Struct/Nullable.hpp"

template <class T>
class Body: public Nullable
{    
    static const int NB_JOINTS = 17;
    static const int JOINT_HEAD = 0;
    static const int JOINT_EYE_L = 1;
    static const int JOINT_EYE_R = 2;
    static const int JOINT_EAR_L = 3;
    static const int JOINT_EAR_R = 4;
    static const int JOINT_SHOULDER_L = 5;
    static const int JOINT_SHOULDER_R = 6;
    static const int JOINT_ELBOW_L = 7;
    static const int JOINT_ELBOW_R = 8;
    static const int JOINT_WRIST_L = 9;
    static const int JOINT_WRIST_R = 10;
    static const int JOINT_HIP_L = 11;
    static const int JOINT_HIP_R = 12;
    static const int JOINT_KNEE_L = 13;
    static const int JOINT_KNEE_R = 14;
    static const int JOINT_ANKLE_L = 15;
    static const int JOINT_ANKLE_R = 16;

public:
    T joints[NB_JOINTS];

    Body();
    Body(T* joints);
    Body(const Body& other);
    ~Body();
};

template<class T>
Body<T>::Body()
{

}

template<class T>
Body<T>::Body(T* joints)
{
    memcpy(this->joints, joints, sizeof(T) * NB_JOINTS);
}

template<class T>
Body<T>::Body(const Body& other)
    : Nullable(other)
{
    memcpy(this->joints, other.joints, sizeof(T) * NB_JOINTS);
}

template<class T>
Body<T>::~Body()
{

}

typedef Body<Vec2f> Body2D;
typedef Body<Vec3f> Body3D;
