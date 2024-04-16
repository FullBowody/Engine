#pragma once
#include <string>
#include <functional>
#include "Event/EventManager.hpp"
#include "Camera/CameraFrameEvent.hpp"
#include "Camera/Capture.hpp"
#include "Updatable.hpp"
#include "Struct/Vec3.hpp"
#include "Struct/Quaternion.hpp"
#include "Tracker/BodyTracker.hpp"
#include "Tracker/ArucoTracker.hpp"

class Camera: public Updatable, public EventManager<CameraFrameEvent>
{
protected:
    Vec3f position;
    Quaternion rotation;

    Capture* cap;
    BodyTracker* bodyTracker;
    ArucoTracker* arucoTracker;

    void setCapture(Capture* cap);

public:
    Camera();
    ~Camera();

    virtual int update(float dt);
    virtual void readDevice(int device);
    virtual void readStream(std::string url);

    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual int getFps() const;
};
