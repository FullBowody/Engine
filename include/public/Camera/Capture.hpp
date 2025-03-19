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

    virtual Transform& onCalibrate() = 0;

public:
    std::string& getType() const;
    Transform& getTransform() const;
    int getWidth() const;
    int getHeight() const;
    CaptureInfo& getInfos() const;
    Image& getImage() const;
    CaptureSkeleton& getSkeleton() const;
    Transform& calibrate();
};