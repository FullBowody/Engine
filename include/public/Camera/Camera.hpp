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

class ENGINE_API Camera: public Identifiable, public Updatable
{
private:
    std::string name;
    PluginHandle<Capture>* capturePlugin;

public:
    Camera();
    Camera(PluginHandle<Capture>* capturePlugin);
    virtual ~Camera();

    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);

    virtual const std::string& getName() const;
    virtual void setName(const std::string& name);

    virtual Capture* getCapture() const;
    virtual void useCapturePlugin(PluginHandle<Capture>* capturePlugin);
    
    virtual FBError estimatePoseFromScene(Scene scene, std::function<void(FBError)> callback);

    virtual FBError startTracking();
    virtual FBError stopTracking();

    virtual FBError startPreview();
    virtual FBError stopPreview();

    virtual FBError onUpdate(float dt);
};
