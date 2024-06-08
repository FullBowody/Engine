#pragma once

#include <vector>
#include "Camera/Camera.hpp"
#include "Updatable.hpp"
#include "utils.hpp"
#include "Plugins/PluginHandle.hpp"
#include "Plugins/CameraPlugin.hpp"
#include "Plugins/PluginProvider.hpp"
#include "Struct/Scene.hpp"

class DLLExport Engine: public Updatable
{
private:
    Scene scene;
    std::vector<PluginHandle<CameraPlugin>*> cameras;
    PluginProvider pluginProvider;

public:
    Engine();
    ~Engine();

    virtual Scene& getScene();
    virtual PluginProvider& getPluginProvider();

    virtual Camera* createCamera(std::string plugin);
    virtual bool destroyCamera(int index);
    virtual bool destroyCamera(Camera* camera);
    virtual Camera* getCamera(int index);
    virtual std::vector<Camera*> getCameras();

    virtual int startTracking();
    virtual int stopTracking();

    virtual int start();
    virtual int update(float dt);
    virtual int stop();
};
