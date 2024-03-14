#pragma once
#include "Event/Event.hpp"
#include "Event/EventManager.hpp"
#include "Camera/CameraFrameEvent.hpp"

class Camera: public EventManager<CameraFrameEvent>
{
private:
    int count;

public:
    Camera();
    ~Camera();

    void update();
};
