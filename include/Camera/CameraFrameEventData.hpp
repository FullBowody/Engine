#include "Event/EventData.hpp"
#include "Camera/Frame.hpp"

class CameraFrameEventData: public EventData
{
private:
    const Frame& frame;

public:
    CameraFrameEventData(const Frame& frame)
        : frame(frame)
    {

    }

    ~CameraFrameEventData()
    {

    }

    const Frame getFrame() const
    {
        return frame;
    }
};
