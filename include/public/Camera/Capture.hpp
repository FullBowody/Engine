#pragma once
#include <string>
#include "Updatable.hpp"
#include "Camera/Image.hpp"
#include "Params/ParamManager.hpp"
#include "Structs/Transform.hpp"
#include "Structs/CaptureInfo.hpp"
#include "Structs/CaptureSkeleton.hpp"
#include "Structs/FBError.hpp"

class Capture : public Updatable, public ParamManager
{
protected:
    int m_width;
    int m_height;
    std::string m_type;
    Transform m_transform;
    Image m_image;
    CaptureInfo m_infos;
    CaptureSkeleton m_skeleton;

    virtual Transform& onCalibrate() = 0;
    virtual FBError onStartTracking() = 0;
    virtual FBError onStopTracking() = 0;
    virtual FBError onStartPreview() = 0;
    virtual FBError onStopPreview() = 0;

    Capture();
    Capture(const std::string& type);

public:
    virtual ~Capture() = default;

    const std::string& getType() const;
    const Transform& getTransform() const;
    int getWidth() const;
    int getHeight() const;
    const CaptureInfo& getInfos() const;
    const Image& getImage() const;
    const CaptureSkeleton& getSkeleton() const;
    const Transform& calibrate();

    virtual FBError startTracking();
    virtual FBError stopTracking();

    virtual FBError startPreview();
    virtual FBError stopPreview();
};
