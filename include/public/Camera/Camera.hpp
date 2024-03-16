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

class Camera: public Updatable, public EventManager<CameraFrameEvent>, public EventListener<CameraFrameEvent>
{
protected:
    Capture* cap;
    Vec3f position;
    Quaternion rotation;

    void setCapture(Capture* cap);

public:
    Camera();
    ~Camera();

    int update(float dt);
    void readDevice(int device);
    void readStream(std::string url);

    void onEvent(const CameraFrameEvent& event);
};
