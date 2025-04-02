#pragma once

#include <vector>
#include <memory>
#include <thread>
#include "Camera/Camera.hpp"
#include "Camera/Capture.hpp"
#include "Structs/Skeleton.hpp"
#include "Structs/Marker.hpp"
#include "Structs/Scene.hpp"
#include "utils.hpp"
#include "Plugins/PluginProvider.hpp"
#include "Plugins/PluginHandle.hpp"
#include "ListenerServer.hpp"

class ENGINE_API Engine
{
protected:
    std::vector<std::shared_ptr<Camera>> cameras;
    std::shared_ptr<Skeleton> skeleton;
    Scene scene;
    PluginProvider pluginProvider;
    ListenerServer listenerServer;
    bool shouldStop = false;
    std::thread updateThread;
    
    virtual FBError onUpdate(float dt);

public:
    Engine();
    ~Engine();

    virtual void setEngineCWD(std::string dirpath);
    virtual PluginProvider& getPluginProvider();
    virtual ListenerServer& getListenerServer();

    virtual std::weak_ptr<Camera> createCamera();
    virtual std::weak_ptr<Camera> getCamera(int index);
    virtual void destroyCamera(int index);
    virtual void destroyCamera(const Camera& camera);
    virtual const std::vector<std::shared_ptr<Camera>>& getCameras();

    virtual std::weak_ptr<Marker> createMarker();
    virtual std::weak_ptr<Marker> getMarker(int index);
    virtual void destroyMarker(int index);
    virtual void destroyMarker(const Marker& marker);
    virtual const std::vector<std::shared_ptr<Marker>>& getMarkers();
    virtual const Scene& getScene();

    virtual std::weak_ptr<Skeleton> getSkeleton();

    virtual FBError startTracking();
    virtual FBError stopTracking();

    virtual FBError start();
    virtual FBError stop();
};
