#include "Camera/CameraFrameEvent.hpp"

CameraFrameEvent::CameraFrameEvent(const Frame& frame)
    : Event<CameraFrameEventData>(CameraFrameEventData(frame))
{
    
}

CameraFrameEvent::CameraFrameEvent(const CameraFrameEvent& event)
    : Event<CameraFrameEventData>(event.data)
{
    
}

CameraFrameEvent::~CameraFrameEvent()
{

}
