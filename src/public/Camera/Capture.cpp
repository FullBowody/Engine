#include "Camera/Capture.hpp"

void Capture::setPreviewImage(const Image& image)
{
    this->image = image;
    eventManager_image.dispatchEvent(image);
}

void Capture::setCaptureSkeleton(const CaptureSkeleton& skeleton)
{
    this->skeleton = std::make_shared<CaptureSkeleton>(skeleton);
    eventManager_skeleton.dispatchEvent(skeleton);
}

Capture::Capture()
    : width(0), height(0), type(""), image(Image())
{
}

Capture::Capture(const std::string& type)
    : width(0), height(0), type(type), image(Image())
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

std::shared_ptr<CaptureSkeleton> Capture::getSkeleton() const
{
    return skeleton;
}

FBError Capture::estimatePoseFromScene(const Scene& scene, std::function<void(const FBError&)> callback)
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

void Capture::addEventListener(std::function<void(const CaptureSkeleton&)> callback)
{
    eventManager_skeleton.addEventListener(callback);
}

void Capture::removeEventListener(std::function<void(const CaptureSkeleton&)> callback)
{
    eventManager_skeleton.removeEventListener(callback);
}

void Capture::addEventListener(std::function<void(const Image&)> callback)
{
    eventManager_image.addEventListener(callback);
}

void Capture::removeEventListener(std::function<void(const Image&)> callback)
{
    eventManager_image.removeEventListener(callback);
}
