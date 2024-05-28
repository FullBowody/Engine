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
    
    int update(float dt);
    int startTracking();
    int stopTracking();
    int calculatePos();

    void onPreview(Callback<Frame>* listener);
    void onPose(Callback<Pose>* listener);
    void onBody(Callback<Body2D>* listener);

    int getWidth() const;
    int getHeight() const;
    const Frame& getPreview() const;
    const Pose& getPose() const;
    const Body2D& getBody(float dt_since_updt) const;
};
