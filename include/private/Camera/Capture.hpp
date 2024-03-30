#pragma once
#include "Updatable.hpp"
#include "Camera/Frame.hpp"
#include "Event/EventManager.hpp"
#include "Camera/CameraFrameEvent.hpp"

class Capture: public Updatable, public EventManager<CameraFrameEvent>
{
protected:
    Capture();

public:
    ~Capture();
};
