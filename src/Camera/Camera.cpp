#include <iostream> 
#include "Camera/Camera.hpp"
#include "Camera/CaptureWebcam.hpp"

Camera::Camera()
{
    cap = new CaptureWebcam(0);
    cap->attachListener(this);
}

Camera::~Camera()
{
    if (cap != nullptr) delete cap;
}

int Camera::update(float dt)
{
    return cap->update(dt);
}

void Camera::onEvent(const CameraFrameEvent& event)
{
    dispatchEvent(event);
}
