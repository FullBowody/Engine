#pragma once

#include <vector>
#include "Camera/Camera.hpp"
#include "Event/EventListener.hpp"
#include "Updatable.hpp"

class Engine: public Updatable
{
private:
    std::vector<Camera*> cameras;

public:
    Engine();
    virtual ~Engine();

    virtual Camera* createCamera();
    virtual int destroyCamera(Camera* camera);

    virtual int start();
    virtual int update(float dt);
    virtual int stop();
};
