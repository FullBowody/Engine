#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <future>
#include "Camera/Camera.hpp"
#include "Camera/Capture.hpp"
#include "Structs/Skeleton.hpp"
#include "Structs/Marker.hpp"
#include "Structs/Scene.hpp"
#include "Structs/FBError.hpp"
#include "utils.hpp"
#include "Plugins/PluginProvider.hpp"
#include "Plugins/PluginHandle.hpp"
#include "ListenerServer.hpp"
#include "ActionThreadable.hpp"

class ENGINE_API Engine : public ActionThreadable
{
protected:
    std::vector<std::shared_ptr<Camera>> cameras;
    std::shared_ptr<Skeleton> skeleton;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<PluginProvider> pluginProvider;
    std::shared_ptr<ListenerServer> listenerServer;
    bool shouldStop = false;
    std::thread updateThread;
    
    virtual FBError onUpdate(float dt);

public:
    Engine();
    virtual ~Engine();

    virtual void setEngineCWD(std::string dirpath);
    virtual std::future<std::shared_ptr<PluginProvider>> getPluginProvider();
    virtual std::future<std::shared_ptr<ListenerServer>> getListenerServer();

    virtual std::future<std::weak_ptr<Camera>> createCamera();
    virtual std::future<std::weak_ptr<Camera>> getCamera(int index);
    virtual std::future<FBError> destroyCamera(int index);
    virtual std::future<FBError> destroyCamera(const Camera& camera);
    virtual std::future<std::reference_wrapper<std::vector<std::shared_ptr<Camera>>>> getCameras();

    virtual std::future<std::shared_ptr<Scene>> getScene();
    virtual std::future<std::weak_ptr<Skeleton>> getSkeleton();

    virtual std::future<FBError> startTracking();
    virtual std::future<FBError> stopTracking();

    virtual FBError start();
    virtual FBError stop();
};
