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
    Pose* pose = nullptr;
    Frame* preview = nullptr;
    Body2D* body = nullptr;

    EventManager<Frame> onPreviewEvent;
    EventManager<Pose> onPoseEvent;
    EventManager<Body2D> onBodyEvent;

protected:
    void setPose(const Pose& pose);
    void setPreview(const Frame& preview);
    void setBody(const Body2D& body);
    bool shouldTrack() const;

    virtual int onUpdate(float dt) = 0;
    virtual int onStartTracking() = 0;
    virtual int onStopTracking() = 0;
    virtual int onCalculatePos() = 0;

public:
    Camera();
    virtual ~Camera();
    
    virtual int update(float dt);
    virtual int startTracking();
    virtual int stopTracking();
    virtual int calculatePos();

    virtual void onPreview(Callback<Frame>* listener);
    virtual void onPose(Callback<Pose>* listener);
    virtual void onBody(Callback<Body2D>* listener);

    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual const Frame& getPreview() const;
    virtual const Pose& getPose() const;
    virtual const Body2D& getBody(float dt_since_updt) const;
};
