#pragma once
#include <string>
#include <functional>
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

typedef std::function<void(const CameraFrameEvent&)> FrameListener;

class Camera: public Updatable, public EventManager<CameraFrameEvent>, public EventListener<CameraFrameEvent>
{
protected:
    std::vector<FrameListener> frameListeners;

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

    virtual const Frame& getFrame() const;

    virtual void onFrame(FrameListener listener);
    virtual void onEvent(const CameraFrameEvent& event);
};
