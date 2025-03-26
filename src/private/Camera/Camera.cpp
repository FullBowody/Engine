#include <iostream>
#include "Camera/Camera.hpp"
#include "utils.hpp"

void Camera::onCaptureSkeleton(const CaptureSkeleton& captureSkeleton)
{
    eventManager_skeleton.dispatchEvent(captureSkeleton);
}

void Camera::onImage(const Image& image)
{
    eventManager_image.dispatchEvent(image);
}

Camera::Camera()
{
    capturePlugin = nullptr;
}

Camera::Camera(PluginHandle<Capture>* capturePlugin)
{
    capturePlugin = capturePlugin;
}

Camera::~Camera()
{
}

std::ostream& operator<<(std::ostream& os, const Camera& camera)
{
    os << "Camera(" << camera.getName() << ")";
    return os;
}

const std::string& Camera::getName() const
{
    return name;
}

void Camera::setName(const std::string& name)
{
    this->name = name;
}

Capture* Camera::getCapture() const
{
    if (!capturePlugin) return nullptr;
    return capturePlugin->getPlugin();
}

void Camera::useCapturePlugin(PluginHandle<Capture>* capturePlugin)
{
    this->capturePlugin = capturePlugin;
}

FBError Camera::estimatePoseFromScene(const Scene& scene, std::function<void(const FBError&)> callback)
{
    if (!capturePlugin)
    {
        std::cerr << "No capture device to estimate pose from scene" << std::endl;
        return FBError::NO_CAPTURE_DEVICE;
    }

    return capturePlugin->getPlugin()->estimatePoseFromScene(scene, callback);
}

FBError Camera::startTracking()
{
    if (!capturePlugin)
    {
        std::cerr << "No capture device to start tracking" << std::endl;
        return FBError::NO_CAPTURE_DEVICE;
    }

    return capturePlugin->getPlugin()->startTracking();
}

FBError Camera::stopTracking()
{
    if (!capturePlugin)
    {
        std::cerr << "No capture device to stop tracking" << std::endl;
        return FBError::NO_CAPTURE_DEVICE;
    }

    return capturePlugin->getPlugin()->stopTracking();
}

FBError Camera::startPreview()
{
    if (!capturePlugin)
    {
        std::cerr << "No capture device to start preview" << std::endl;
        return FBError::NO_CAPTURE_DEVICE;
    }

    return capturePlugin->getPlugin()->startPreview();
}

FBError Camera::stopPreview()
{
    if (!capturePlugin)
    {
        std::cerr << "No capture device to stop preview" << std::endl;
        return FBError::NO_CAPTURE_DEVICE;
    }

    return capturePlugin->getPlugin()->stopPreview();
}

void Camera::addEventListener(std::function<void(const CaptureSkeleton&)> callback)
{
    eventManager_skeleton.addEventListener(callback);
}

void Camera::removeEventListener(std::function<void(const CaptureSkeleton&)> callback)
{
    eventManager_skeleton.removeEventListener(callback);
}

void Camera::addEventListener(std::function<void(const Image&)> callback)
{
    eventManager_image.addEventListener(callback);
}

void Camera::removeEventListener(std::function<void(const Image&)> callback)
{
    eventManager_image.removeEventListener(callback);
}

FBError Camera::onUpdate(float dt)
{
    if (capturePlugin)
    {
        CHECK_ERRORS(capturePlugin->getPlugin()->update(dt));
    }

    return FBError::OK;
}
