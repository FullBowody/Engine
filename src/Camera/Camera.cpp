#include <iostream> 
#include "Camera/Camera.hpp"

Camera::Camera()
{
    count = 0;
}

Camera::~Camera()
{

}

void Camera::update()
{
    if (count++ > 100)
    {
        Frame frame;
        CameraFrameEvent event(frame);
        dispatchEvent(event);
        count = 0;
    }
}
