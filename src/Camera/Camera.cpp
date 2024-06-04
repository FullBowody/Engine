#include <iostream> 
#include "Camera/Camera.hpp"

Camera::Camera()
{

}

Camera::~Camera()
{
    if (pose) delete pose;
    if (preview) delete preview;
    if (body) delete body;
}

void Camera::setPose(const Pose& pose)
{
    this->pose = new Pose(pose);
    onPoseEvent.dispatchEvent(*this->pose);
}

void Camera::setPreview(const Frame& preview)
{
    if (this->preview) delete this->preview;
    this->preview = new Frame(preview);
    this->width = this->preview->getWidth();
    this->height = this->preview->getHeight();
    onPreviewEvent.dispatchEvent(*this->preview);
}

void Camera::setBody(const Body2D& body)
{
    this->body = new Body2D(body);
    onBodyEvent.dispatchEvent(*this->body);
}

void Camera::setMarkers(const std::vector<Marker>& markers)
{
    this->markers = std::vector<Marker>(markers);
    // TODO : maybe dispatch an event
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
    if (_shouldTrack) return 0;
    _shouldTrack = true;
    return onStartTracking();
}

int Camera::stopTracking()
{
    if (!_shouldTrack) return 0;
    _shouldTrack = false;
    return onStopTracking();
}

int Camera::detectMarkers()
{
    return onDetectMarkers();
}

void Camera::onPreview(Callback<Frame>* listener)
{
    onPreviewEvent.attachListener(listener);
}

void Camera::onPose(Callback<Pose>* listener)
{
    onPoseEvent.attachListener(listener);
}

void Camera::onBody(Callback<Body2D>* listener)
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
    return *preview;
}

const Pose& Camera::getPose() const
{
    return *pose;
}

const Body2D& Camera::getBody(float dt_since_updt) const
{
    // TODO : add a [oldBody] member to the class
    // and use it to interpolate / predict the body
    // for call behond the last update
    // (maybe add a [bool interpolate = false] flag to the function)
    return *body;
}

const std::vector<Marker>& Camera::getDetectedMarkers() const
{
    return markers;
}

std::ostream& operator<<(std::ostream& os, const Camera& camera)
{
    os << "Camera(width=" << camera.width << ", height=" << camera.height << ", pose=" << printPtr(camera.pose) << ")";
    return os;
}
