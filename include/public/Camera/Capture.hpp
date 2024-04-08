#pragma once
#include "Updatable.hpp"
#include "Camera/Frame.hpp"
#include "Event/EventManager.hpp"
#include "Camera/CameraFrameEvent.hpp"

class Capture: public Updatable, public EventManager<CameraFrameEvent>
{
protected:
    Frame frame;
    Capture();

public:
    ~Capture();

    virtual const Frame& getFrame() const = NULL;
};
