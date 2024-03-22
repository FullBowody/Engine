#pragma once
#include "Event/EventListener.hpp"
#include "Camera/CameraFrameEvent.hpp"
#include "Struct/Vec2.hpp"
#include "Struct/Vec3.hpp"
#include "Struct/Quaternion.hpp"

class ArucoTracker: public EventListener<CameraFrameEvent>
{
private:
    Vec3f position;
    Quaternion rotation;

public:
    ArucoTracker();
    ~ArucoTracker();

    const Vec3f getTrackedPosition() const;
    const Quaternion getTrackedRotation() const;

    void onEvent(const CameraFrameEvent& event);
};
