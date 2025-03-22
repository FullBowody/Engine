#include "Structs/CaptureJoint.hpp"
#include <ostream>
#include <glm/glm.hpp>

CaptureJoint::CaptureJoint()
    : position(glm::vec3(0.0f)), confidence(0.0f)
{

}

CaptureJoint::CaptureJoint(const glm::vec3& position, float confidence)
    : position(position), confidence(confidence)
{

}

CaptureJoint::CaptureJoint(const CaptureJoint& joint)
    : position(joint.position), confidence(joint.confidence)
{

}

CaptureJoint::~CaptureJoint()
{

}

CaptureJoint& CaptureJoint::operator=(const CaptureJoint& other)
{
    position = other.position;
    confidence = other.confidence;

    return *this;
}

bool CaptureJoint::operator==(const CaptureJoint& other) const
{
    return position == other.position && confidence == other.confidence;
}

bool CaptureJoint::operator!=(const CaptureJoint& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CaptureJoint& joint)
{
    os << "CaptureJoint(position=(x=" << joint.position.x << ", y=" << joint.position.y << ", z="
       << joint.position.z << "), rotation=" << joint.confidence << ")";
    return os;
}

void CaptureJoint::setPosition(const glm::vec3& position)
{
    this->position = position;
}

void CaptureJoint::setConfidence(float confidence)
{
    confidence = confidence;
}

glm::vec3 CaptureJoint::getPosition() const
{
    return position;
}

float CaptureJoint::getConfidence() const
{
    return confidence;
}
