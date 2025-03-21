#include "Structs/CaptureJoint.hpp"
#include <ostream>
#include <glm/glm.hpp>

CaptureJoint::CaptureJoint()
    : m_position(glm::vec3(0.0f)), m_confidence(0.0f)
{

}

CaptureJoint::CaptureJoint(const glm::vec3& position, float confidence)
    : m_position(position), m_confidence(confidence)
{

}

CaptureJoint::CaptureJoint(const CaptureJoint& joint)
    : m_position(joint.m_position), m_confidence(joint.m_confidence)
{

}

CaptureJoint::~CaptureJoint()
{

}

CaptureJoint& CaptureJoint::operator=(const CaptureJoint& other)
{
    m_position = other.m_position;
    m_confidence = other.m_confidence;

    return *this;
}

bool CaptureJoint::operator==(const CaptureJoint& other) const
{
    return m_position == other.m_position && m_confidence == other.m_confidence;
}

bool CaptureJoint::operator!=(const CaptureJoint& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CaptureJoint& joint)
{
    os << "CaptureJoint(position=(x=" << joint.m_position.x << ", y=" << joint.m_position.y << ", z="
       << joint.m_position.z << "), rotation=" << joint.m_confidence << ")";
    return os;
}

void CaptureJoint::setPosition(const glm::vec3& position)
{
    m_position = position;
}

void CaptureJoint::setConfidence(float confidence)
{
    m_confidence = confidence;
}

glm::vec3 CaptureJoint::getPosition() const
{
    return m_position;
}

float CaptureJoint::getConfidence() const
{
    return m_confidence;
}
