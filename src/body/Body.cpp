#include "Body.hpp"

Body* Body::getInstance()
{
    if (instance == nullptr)
        new Body();
    return instance;
}

Body::Body()
{
    if (Body::instance == nullptr)
        delete Body::instance;
    Body::instance = this;

    joints.clear();
    for(int i = 0; i < Joint::JOINT_COUNT; i++)
        joints.push_back(BodyJoint());
}

Body::~Body()
{

}