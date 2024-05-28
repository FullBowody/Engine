#pragma once

#include <vector>
#include "Camera/Camera.hpp"
#include "Updatable.hpp"
#include "utils.hpp"
#include "Plugins/PluginHandle.hpp"
#include "Plugins/CameraPlugin.hpp"

class DLLExport Engine: public Updatable
{
private:
    std::vector<PluginHandle<CameraPlugin>*> cameras;

public:
    Engine();
    ~Engine();

    Camera* createCamera(std::string plugin);
    bool destroyCamera(int index);
    bool destroyCamera(Camera* camera);
    Camera* getCamera(int index);
    std::vector<Camera*> getCameras();

    int start();
    int update(float dt);
    int stop();
};
