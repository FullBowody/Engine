#pragma once
#include <string>
#include "Event/Event.hpp"
#include "Event/EventManager.hpp"
#include "Event/EventListener.hpp"
#include "Camera/CameraFrameEvent.hpp"
#include "Camera/Capture.hpp"
#include "Updatable.hpp"
#include "Struct/Vec3.hpp"
#include "Struct/Quaternion.hpp"
#include "Tracker/BodyTracker.hpp"
#include "Tracker/ArucoTracker.hpp"

class Camera: public Updatable, public EventManager<CameraFrameEvent>, public EventListener<CameraFrameEvent>
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

    virtual void onFrame(EventListener<CameraFrameEvent>* listener);
    virtual void onEvent(const CameraFrameEvent& event);
};
