#pragma once
#include "Camera/CameraFrameEvent.hpp"
#include "Struct/Vec2.hpp"
#include "Struct/Vec3.hpp"
#include "Struct/Quaternion.hpp"

class ArucoTracker
{
private:
    Vec3f position;
    Quaternion rotation;

public:
    ArucoTracker();
    ~ArucoTracker();

    const Vec3f getTrackedPosition() const;
    const Quaternion getTrackedRotation() const;

    void onCameraFrame(const CameraFrameEvent& event);
};
