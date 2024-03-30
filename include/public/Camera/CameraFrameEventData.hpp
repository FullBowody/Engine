#pragma once
#include "Event/EventData.hpp"
#include "Camera/Frame.hpp"
#include <iostream>

class CameraFrameEventData: public EventData
{
private:
    Frame frame;

public:
    CameraFrameEventData(const Frame& frame);
    CameraFrameEventData(const CameraFrameEventData& data);
    ~CameraFrameEventData();

    virtual const Frame& getFrame() const;
};
