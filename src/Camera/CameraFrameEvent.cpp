#include "Camera/CameraFrameEvent.hpp"

CameraFrameEvent::CameraFrameEvent(const Frame& frame)
    : frame(frame)
{
    
}

CameraFrameEvent::CameraFrameEvent(const CameraFrameEvent& event)
    : frame(event.frame)
{
    
}

CameraFrameEvent::~CameraFrameEvent()
{

}

const Frame& CameraFrameEvent::getFrame() const
{
    return frame;
}
