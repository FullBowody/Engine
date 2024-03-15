#pragma once
#include "Event/EventData.hpp"
#include "Camera/Frame.hpp"
#include <iostream>

class CameraFrameEventData: public EventData
{
private:
    Frame frame;

public:
    CameraFrameEventData(const Frame& frame)
        : frame(frame)
    {
        
    }

    CameraFrameEventData(const CameraFrameEventData& data)
        : frame(data.frame)
    {
        
    }

    ~CameraFrameEventData()
    {

    }

    const Frame& getFrame() const
    {
        return frame;
    }
};
