#pragma once
#include "Event/Event.hpp"
#include "Camera/CameraFrameEventData.hpp"

class CameraFrameEvent: public Event<CameraFrameEventData>
{
private:
    
public:
    CameraFrameEvent(const Frame& frame)
        : Event<CameraFrameEventData>(CameraFrameEventData(frame))
    {
        
    }

    CameraFrameEvent(const CameraFrameEvent& event)
        : Event<CameraFrameEventData>(event.data)
    {
        
    }
    
    ~CameraFrameEvent()
    {

    }
};
