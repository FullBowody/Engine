#pragma once
#include <string>
#include "utils.hpp"
#include "Updatable.hpp"
#include "Camera/Image.hpp"
#include "Params/ParamManager.hpp"
#include "Plugins/PluginHandle.hpp"
#include "Structs/Transform.hpp"
#include "Structs/CaptureInfo.hpp"
#include "Structs/CaptureSkeleton.hpp"
#include "Structs/FBError.hpp"
#include "Structs/Scene.hpp"

class ENGINE_API Capture : public Updatable, public ParamManager
{
protected:
    int width;
    int height;
    std::string type;
    Transform transform;
    Image image;
    CaptureInfo infos;
    CaptureSkeleton skeleton;

    virtual FBError onStartTracking() = 0;
    virtual FBError onStopTracking() = 0;
    virtual FBError onStartPreview() = 0;
    virtual FBError onStopPreview() = 0;
    virtual FBError onEstimatePoseFromScene(const Scene& scene, std::function<void(const FBError&)> callback) = 0;

    Capture();
    Capture(const std::string& type);

public:
    virtual ~Capture() = default;

    virtual const std::string& getType() const;
    virtual const Transform& getTransform() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual const CaptureInfo& getInfos() const;
    virtual const Image& getImage() const;
    virtual const CaptureSkeleton& getSkeleton() const;
    
    virtual FBError estimatePoseFromScene(const Scene& scene, std::function<void(const FBError&)> callback);

    virtual FBError startTracking();
    virtual FBError stopTracking();
    virtual FBError startPreview();
    virtual FBError stopPreview();
};
