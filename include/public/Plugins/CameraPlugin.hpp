#pragma once
#include "Camera/Camera.hpp"

class DLLExport CameraPlugin: public Camera
{
public:
    CameraPlugin();
    ~CameraPlugin();
    
    virtual int onUpdate(float dt);
    virtual int onStartTracking();
    virtual int onStopTracking();
    virtual int onCalculatePos();
};
