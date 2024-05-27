#pragma once
#include <string>
#include <functional>
#include "Event/EventManager.hpp"
#include "Updatable.hpp"
#include "Struct/Pose.hpp"
#include "Struct/Body.hpp"
#include "Camera/Frame.hpp"
#include "Param/ParamManager.hpp"

class DLLExport Camera: public Updatable, public ParamManager
{
private:
    int width;
    int height;
    bool _shouldTrack;
    Pose pose;
    Frame preview;
    Body2D body;

    EventManager<const Frame&> onPreviewEvent;
    EventManager<const Pose&> onPoseEvent;
    EventManager<const Body2D&> onBodyEvent;

protected:
    void setPose(Pose pose);
    void setPreview(Frame preview);
    void setBody(Body2D body);
    bool shouldTrack() const;

    virtual int onUpdate(float dt) = 0;
    virtual int onStartTracking() = 0;
    virtual int onStopTracking() = 0;
    virtual int onCalculatePos() = 0;

public:
    Camera();
    virtual ~Camera();
    
    int update(float dt);
    int startTracking();
    int stopTracking();
    int calculatePos();

    void onPreview(Callback<const Frame&>* listener);
    void onPose(Callback<const Pose&>* listener);
    void onBody(Callback<const Body2D&>* listener);

    int getWidth() const;
    int getHeight() const;
    const Frame& getPreview() const;
    const Pose& getPose() const;
    const Body2D& getBody(float dt_since_updt) const;
};
