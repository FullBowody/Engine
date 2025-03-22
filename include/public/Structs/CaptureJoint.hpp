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

    CaptureJoint& operator=(const CaptureJoint& other);
    bool operator==(const CaptureJoint& other) const;
    bool operator!=(const CaptureJoint& other) const;
    friend std::ostream& operator<<(std::ostream& os, const CaptureJoint& joint);

    void setPosition(const glm::vec3& position);
    void setConfidence(float confidence);
    glm::vec3 getPosition() const;
    float getConfidence() const;
};
