#pragma once
#include <ostream>
#include <glm/glm.hpp>
#include "utils.hpp"

class ENGINE_API CaptureJoint
{
private:
    glm::vec3 position;
    float confidence;

public:
    CaptureJoint();
    CaptureJoint(const glm::vec3& position, float confidence);
    CaptureJoint(const CaptureJoint& joint);
    virtual ~CaptureJoint();

    virtual CaptureJoint& operator=(const CaptureJoint& other);
    virtual bool operator==(const CaptureJoint& other) const;
    virtual bool operator!=(const CaptureJoint& other) const;
    friend std::ostream& operator<<(std::ostream& os, const CaptureJoint& joint);

    virtual void setPosition(const glm::vec3& position);
    virtual void setConfidence(float confidence);
    virtual glm::vec3 getPosition() const;
    virtual float getConfidence() const;
};
