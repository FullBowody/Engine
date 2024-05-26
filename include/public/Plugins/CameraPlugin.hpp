#pragma once
#include "Camera/Camera.hpp"

class CameraPlugin: public Camera
{
public:
    CameraPlugin();
    ~CameraPlugin();
    
    virtual int onUpdate(float dt);
    virtual int onStartTracking();
    virtual int onStopTracking();
    virtual int onCalculatePos();
};
