#pragma once
#include "Struct/Body.hpp"
#include "Camera/CameraFrameEvent.hpp"

class BodyTracker
{
private:
    Body2D body;

public:
    BodyTracker();
    ~BodyTracker();

    void onCameraFrame(const CameraFrameEvent& event);

    const Body2D getTrackedBody() const;
};
