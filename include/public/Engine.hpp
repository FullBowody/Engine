#pragma once

#include <vector>
#include "Camera/Camera.hpp"
#include "Event/EventListener.hpp"
#include "Updatable.hpp"

class Engine: public Updatable, private EventListener<CameraFrameEvent>
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

    void onEvent(const CameraFrameEvent& event);
};
