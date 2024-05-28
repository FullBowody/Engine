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

    virtual Camera* createCamera(std::string plugin);
    virtual bool destroyCamera(int index);
    virtual bool destroyCamera(Camera* camera);
    virtual Camera* getCamera(int index);
    virtual std::vector<Camera*> getCameras();

    virtual int start();
    virtual int update(float dt);
    virtual int stop();
};
