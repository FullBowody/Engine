#pragma once
#include "Event/EventData.hpp"
#include "Camera/Frame.hpp"
#include <iostream>

class CameraFrameEventData: public EventData
{
public:
    const Frame& frame;

    CameraFrameEventData(const Frame& frame)
        : frame(frame)
    {
        std::cout << "> Storing frame of address " << &frame << " to " << &this->frame << " as " << this << std::endl;
        std::cout << "  frame dims = " << frame.width << "x" << frame.height << std::endl;
        std::cout << "  this object dims = " << this->frame.width << "x" << this->frame.height << std::endl;
    }

    ~CameraFrameEventData()
    {

    }
};
