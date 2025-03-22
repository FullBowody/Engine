#include "Camera/Capture.hpp"

Capture::Capture()
    : width(0), height(0), type("")
{
}

Capture::Capture(const std::string& type)
    : width(0), height(0), type(type)
{
}

const std::string& Capture::getType() const
{
    return type;
}

const Transform& Capture::getTransform() const
{
    return transform;
}

int Capture::getWidth() const
{
    return width;
}

int Capture::getHeight() const
{
    return height;
}

const CaptureInfo& Capture::getInfos() const
{
    return infos;
}

const Image& Capture::getImage() const
{
    return image;
}

const CaptureSkeleton& Capture::getSkeleton() const
{
    return skeleton;
}

FBError Capture::estimatePoseFromScene(Scene scene, std::function<void(FBError)> callback)
{
    return onEstimatePoseFromScene(scene, callback);
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
