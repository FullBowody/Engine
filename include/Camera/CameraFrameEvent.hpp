#include "Event/Event.hpp"
#include "CameraFrameEventData.hpp"

class CameraFrameEvent: public Event<CameraFrameEventData>
{
private:
    
public:
    CameraFrameEvent(const Frame& frame)
        : Event<CameraFrameEventData>(CameraFrameEventData(frame))
    {

    }
    
    ~CameraFrameEvent()
    {

    }
};
