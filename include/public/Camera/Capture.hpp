#pragma once
#include "Updatable.hpp"
#include "Camera/Frame.hpp"
#include "Event/EventManager.hpp"
#include "Camera/CameraFrameEvent.hpp"

class Capture: public Updatable, public EventManager<CameraFrameEvent>
{
protected:
    int width;
    int height;
    int fps;
    Capture();

public:
    virtual ~Capture();
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual int getFps() const;
};
