#include <iostream> 
#include "Camera/Camera.hpp"

Camera::Camera()
{
    
}

Camera::~Camera()
{
    
}

void Camera::setPose(Pose pose)
{
    this->pose = pose;
    onPoseEvent.dispatchEvent(this->pose);
}

void Camera::setPreview(Frame preview)
{
    this->preview = preview;
    this->width = preview.getWidth();
    this->height = preview.getHeight();
    onPreviewEvent.dispatchEvent(this->preview);
}

void Camera::setBody(Body2D body)
{
    this->body = body;
    onBodyEvent.dispatchEvent(this->body);
}

bool Camera::shouldTrack() const
{
    return _shouldTrack;
}

int Camera::update(float dt)
{
    return onUpdate(dt);
}

int Camera::startTracking()
{
    _shouldTrack = true;
    return onStartTracking();
}

int Camera::stopTracking()
{
    _shouldTrack = false;
    return onStopTracking();
}

int Camera::calculatePos()
{
    return onCalculatePos();
}

void Camera::onPreview(Callback<const Frame&>* listener)
{
    onPreviewEvent.attachListener(listener);
}

void Camera::onPose(Callback<const Pose&>* listener)
{
    onPoseEvent.attachListener(listener);
}

void Camera::onBody(Callback<const Body2D&>* listener)
{
    onBodyEvent.attachListener(listener);
}

int Camera::getWidth() const
{
    return width;
}

int Camera::getHeight() const
{
    return height;
}

const Frame& Camera::getPreview() const
{
    return preview;
}

const Pose& Camera::getPose() const
{
    return pose;
}

const Body2D& Camera::getBody(float dt_since_updt) const
{
    // TODO : add a [oldBody] member to the class
    // and use it to interpolate / predict the body
    // for call behond the last update
    return body;
}
