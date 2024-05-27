#pragma once

#include <vector>
#include "Camera/Camera.hpp"
#include "Updatable.hpp"
#include "utils.hpp"

class DLLExport Engine: public Updatable
{
private:
    std::vector<Camera*> cameras;

public:
    Engine();
    ~Engine();

    Camera* createCamera();
    bool destroyCamera(int index);
    bool destroyCamera(Camera* camera);
    Camera* getCamera(int index);
    const std::vector<Camera*>& getCameras();

    int start();
    int update(float dt);
    int stop();
};
