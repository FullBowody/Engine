#include <iostream> 
#include "Camera/Camera.hpp"
#include "Camera/CaptureWebcam.hpp"
#include "Camera/CaptureStream.hpp"

void Camera::setCapture(Capture* cap)
{
    if (this->cap) delete this->cap;
    this->cap = cap;
    this->cap->attachListener([this](const CameraFrameEvent& event) {
        if (this->bodyTracker) this->bodyTracker->onCameraFrame(event);
        if (this->arucoTracker) this->arucoTracker->onCameraFrame(event);
        this->dispatchEvent(event);
    });
}

Camera::Camera()
{
    this->cap = nullptr;
    this->bodyTracker = nullptr;
    this->arucoTracker = nullptr;
}

Camera::~Camera()
{
    if (cap) delete cap;
    if (bodyTracker) delete bodyTracker;
    if (arucoTracker) delete arucoTracker;
}

int Camera::update(float dt)
{
    int res = 0;
    if (cap) res = cap->update(dt);
    return res;
}

void Camera::readDevice(int device)
{
    setCapture(new CaptureWebcam(device));
}

void Camera::readStream(std::string url)
{
    setCapture(new CaptureStream(url));
}

int Camera::getWidth() const
{
    if (!cap) return 0;
    return cap->getWidth();
}

int Camera::getHeight() const
{
    if (!cap) return 0;
    return cap->getHeight();
}

int Camera::getFps() const
{
    if (!cap) return 0;
    return cap->getFps();
}
