#pragma once

#include <vector>
#include <memory>
#include "Camera/Camera.hpp"
#include "Structs/Skeleton.hpp"
#include "Structs/Marker.hpp"
#include "Updatable.hpp"
#include "utils.hpp"
#include "Plugins/PluginHandle.hpp"
#include "Plugins/CameraPlugin.hpp"
#include "Plugins/PluginProvider.hpp"

class DLLExport Engine: public Updatable
{
protected:
    std::vector<std::shared_ptr<Marker>> markers;
    std::vector<std::shared_ptr<Camera>> cameras;
    std::shared_ptr<Skeleton> skeleton;
    PluginProvider pluginProvider;
    
    virtual FBError onUpdate(float dt);

public:
    Engine();
    ~Engine();

    virtual void setEngineCWD(std::string dirpath);
    virtual PluginProvider& getPluginProvider();

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

    virtual std::weak_ptr<Skeleton> getSkeleton();

    virtual FBError startTracking();
    virtual FBError stopTracking();
};
