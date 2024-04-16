#pragma once
#include "Camera/Frame.hpp"
#include <iostream>

class CameraFrameEvent
{
private:
    Frame frame;

public:
    CameraFrameEvent(const Frame& frame);
    CameraFrameEvent(const CameraFrameEvent& data);
    ~CameraFrameEvent();

    virtual const Frame& getFrame() const;
};
