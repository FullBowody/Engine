#pragma once
#include "Event/Event.hpp"
#include "Event/EventManager.hpp"
#include "Event/EventListener.hpp"
#include "Camera/CameraFrameEvent.hpp"
#include "Camera/Capture.hpp"
#include "Updatable.hpp"

class Camera: public Updatable, public EventManager<CameraFrameEvent>, public EventListener<CameraFrameEvent>
{
private:
    Capture* cap;

public:
    Camera();
    ~Camera();

    int update(float dt);

    void onEvent(const CameraFrameEvent& event);
};
