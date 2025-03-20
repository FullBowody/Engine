#pragma once

#include <string>
#include "Structs/Transform.hpp"
#include "Camera/Image.hpp"
#include "Structs/CaptureInfo.hpp"
#include "Structs/CaptureSkeleton.hpp"

class Capture
{
private:
    int m_width;
    int m_height;
    std::string m_type;
    Transform m_transform;
    Image m_image;
    CaptureInfo m_infos;
    CaptureSkeleton m_skeleton;

    virtual Transform& onCalibrate() = 0;

public:
    const std::string& getType() const;
    const Transform& getTransform() const;
    int getWidth() const;
    int getHeight() const;
    const CaptureInfo& getInfos() const;
    const Image& getImage() const;
    const CaptureSkeleton& getSkeleton() const;
    const Transform& calibrate();
};
