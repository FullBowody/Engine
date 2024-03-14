#pragma once

#include <vector>
#include "Camera/Camera.hpp"
// #include "Event/EventListener.hpp"

class Engine: private EventListener<CameraFrameEvent>  // TODO : remove this (for testing only)
{
private:
    std::vector<Camera*> cameras;

public:
    Engine();
    ~Engine();

    virtual Camera* createCamera();
    virtual int destroyCamera(Camera* camera);

    virtual int start();
    virtual int update(float dt);
    virtual int stop();

    void onEvent(const CameraFrameEvent& event);  // TODO : remove this (for testing only)
};
