#pragma once
#include <string>
#include <ostream>
#include <functional>
#include "Identifiable.hpp"
#include "Updatable.hpp"
#include "Structs/FBError.hpp"
#include "Structs/Scene.hpp"
#include "Camera/Capture.hpp"
#include "Plugins/PluginHandle.hpp"
#include "Event/EventManager.hpp"
#include "Structs/CaptureSkeleton.hpp"
#include "Camera/Image.hpp"

class ENGINE_API Camera: public Identifiable, public Updatable
{
private:
    std::string name;
    PluginHandle<Capture>* capturePlugin;
    EventManager<CaptureSkeleton> eventManager_skeleton;
    EventManager<Image> eventManager_image;

    void onCaptureSkeleton(const CaptureSkeleton& captureSkeleton);
    void onImage(const Image& image);

public:
    Camera();
    Camera(PluginHandle<Capture>* capturePlugin);
    virtual ~Camera();

    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);

    virtual const std::string& getName() const;
    virtual void setName(const std::string& name);

    virtual Capture* getCapture() const;
    virtual void useCapturePlugin(PluginHandle<Capture>* capturePlugin);
    
    virtual FBError estimatePoseFromScene(const Scene& scene, std::function<void(const FBError&)> callback);

    virtual FBError startTracking();
    virtual FBError stopTracking();
    virtual FBError startPreview();
    virtual FBError stopPreview();

    virtual void addEventListener(std::function<void(const CaptureSkeleton&)> callback);
    virtual void removeEventListener(std::function<void(const CaptureSkeleton&)> callback);
    virtual void addEventListener(std::function<void(const Image&)> callback);
    virtual void removeEventListener(std::function<void(const Image&)> callback);

    virtual FBError onUpdate(float dt);
};
