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
    ~Engine();

    virtual Camera* createCamera();
    virtual bool destroyCamera(int index);
    virtual bool destroyCamera(Camera* camera);
    virtual Camera* getCamera(int index);
    virtual const std::vector<Camera*>& getCameras();

    virtual int start();
    virtual int update(float dt);
    virtual int stop();
};
