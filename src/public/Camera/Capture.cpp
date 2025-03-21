#include "Camera/Capture.hpp"

Capture::Capture()
    : m_width(0), m_height(0), m_type("")
{
}

Capture::Capture(const std::string& type)
    : m_width(0), m_height(0), m_type(type)
{
}

const std::string& Capture::getType() const
{
    return m_type;
}

const Transform& Capture::getTransform() const
{
    return m_transform;
}

int Capture::getWidth() const
{
    return m_width;
}

int Capture::getHeight() const
{
    return m_height;
}

const CaptureInfo& Capture::getInfos() const
{
    return m_infos;
}

const Image& Capture::getImage() const
{
    return m_image;
}

const CaptureSkeleton& Capture::getSkeleton() const
{
    return m_skeleton;
}

const Transform& Capture::calibrate()
{
    return onCalibrate();
}

FBError Capture::startTracking()
{
    return onStartTracking();
}

FBError Capture::stopTracking()
{
    return onStopTracking();
}

FBError Capture::startPreview()
{
    return onStartPreview();
}

FBError Capture::stopPreview()
{
    return onStopPreview();
}
