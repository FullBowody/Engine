#pragma once
#include "Camera/Camera.hpp"

class DLLExport CameraPlugin: public Camera
{
protected:
    virtual int onUpdate(float dt) = 0;
    virtual int onStartTracking() = 0;
    virtual int onStopTracking() = 0;
    virtual int onCalculatePos() = 0;

public:
    CameraPlugin();
    ~CameraPlugin();
};
