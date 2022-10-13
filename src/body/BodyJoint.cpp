#include "BodyJoint.hpp"

BodyJoint::BodyJoint()
{
    this->position = Position();
    this->rotation = Rotation();
    this->confidence = -1;
}

BodyJoint::BodyJoint()
{
    this->position = Position();
    this->rotation = Rotation();
}

BodyJoint::BodyJoint(Position position, Rotation rotation, unsigned char confidence)
{
    this->position = position;
    this->rotation = rotation;
    this->confidence = confidence;
}

BodyJoint::~BodyJoint()
{
}

void BodyJoint::setPosition(Position position)
{
    this->position = position;
}

void BodyJoint::setRotation(Rotation rotation)
{
    this->rotation = rotation;
}

void BodyJoint::setConfidence(unsigned char confidence)
{
    this->confidence = confidence;
}

Position BodyJoint::getPosition()
{
    return this->position;
}

Rotation BodyJoint::getRotation()
{
    return this->rotation;
}

unsigned char BodyJoint::getConfidence()
{
    return this->confidence;
}

bool BodyJoint::fromBuffer(std::vector<unsigned char> buff)
{
    this->fromBuffer(buff, 0);
}

bool BodyJoint::fromBuffer(std::vector<unsigned char> buff, unsigned int offset)
{
    // sizeof position + rotation + confidence
    size_t shift_uchar = sizeof(unsigned char);
    size_t shift_float = sizeof(float);

    if (buff.size() < offset + shift_float * 3 + shift_float * 4 + shift_uchar)
        return false;

    this->position.setX( *((float*)&buff[offset + 0]) );
    this->position.setY( *((float*)&buff[offset + shift_float]) );
    this->position.setZ( *((float*)&buff[offset + shift_float * 2]) );
    
    this->rotation.setX( *((float*)&buff[offset + shift_float * 3]) );
    this->rotation.setY( *((float*)&buff[offset + shift_float * 4]) );
    this->rotation.setZ( *((float*)&buff[offset + shift_float * 5]) );
    this->rotation.setW( *((float*)&buff[offset + shift_float * 6]) );

    this->confidence = buff[offset + shift_float * 7];

    return true;
}

std::vector<unsigned char> BodyJoint::toBuffer()
{
    size_t shift_uchar = sizeof(unsigned char);
    size_t shift_float = sizeof(float);

    // size of position + rotation + confidence
    std::vector<unsigned char> buff(shift_float * 3 + shift_float * 4 + shift_uchar);

    *((float*)&buff[0])               = this->position.getX();
    *((float*)&buff[shift_float])     = this->position.getY();
    *((float*)&buff[shift_float * 2]) = this->position.getZ();
    
    *((float*)&buff[shift_float * 3]) = this->rotation.getX();
    *((float*)&buff[shift_float * 4]) = this->rotation.getY();
    *((float*)&buff[shift_float * 5]) = this->rotation.getZ();
    *((float*)&buff[shift_float * 6]) = this->rotation.getW();

    buff[shift_float * 7] = this->confidence;

    return buff;
}