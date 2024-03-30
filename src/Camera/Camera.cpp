#include <iostream> 
#include "Camera/Camera.hpp"
#include "Camera/CaptureWebcam.hpp"
#include "Camera/CaptureStream.hpp"

void Camera::setCapture(Capture* cap)
{
    if (this->cap) delete this->cap;
    this->cap = cap;
    this->cap->attachListener(this);
}

Camera::Camera()
{
    this->cap = nullptr;
    this->bodyTracker = new BodyTracker();
    this->attachListener(bodyTracker);
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

void Camera::onFrame(EventListener<CameraFrameEvent>* listener)
{
    this->attachListener(listener);
}

void Camera::onEvent(const CameraFrameEvent& event)
{
    std::cout << "Camera received event from capture, dispatching." << std::endl;
    std::cout << " &f = " << &(event.getData().getFrame()) << std::endl;
    dispatchEvent(event);
}
