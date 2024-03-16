#pragma once
#include "Struct/Body.hpp"
#include "Event/EventListener.hpp"
#include "Camera/CameraFrameEvent.hpp"

class BodyTracker: public EventListener<CameraFrameEvent>
{
private:
    Body2D body;

public:
    BodyTracker();
    ~BodyTracker();

    void onEvent(const CameraFrameEvent& event);

    const Body2D getTrackedBody() const;
};
