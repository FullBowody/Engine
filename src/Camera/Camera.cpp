#include <iostream> 
#include "Camera/Camera.hpp"
#include "Camera/CaptureWebcam.hpp"
#include "Camera/CaptureStream.hpp"

void Camera::setCapture(Capture* cap)
{
    if (this->cap != nullptr) delete this->cap;
    this->cap = cap;
    this->cap->attachListener(this);
}

Camera::Camera()
{
    
}

Camera::~Camera()
{
    if (cap != nullptr) delete cap;
}

int Camera::update(float dt)
{
    int res = 0;
    if (cap != nullptr)
        res = cap->update(dt);
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

void Camera::onEvent(const CameraFrameEvent& event)
{
    dispatchEvent(event);
}
