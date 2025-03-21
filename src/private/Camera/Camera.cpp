#include "Camera/Camera.hpp"

Camera::Camera()
{
    m_capture = nullptr;
}

Camera::Camera(std::shared_ptr<Capture> capture)
{
    m_capture = capture;
}

Camera::~Camera()
{
}

std::ostream& operator<<(std::ostream& os, const Camera& camera)
{
    os << "Camera(" << camera.getName() << ")";
    return os;
}

const std::string& Camera::getName() const
{
    return m_name;
}

void Camera::setName(const std::string& name)
{
    m_name = name;
}

std::weak_ptr<Capture> Camera::getCapture() const
{
    return m_capture;
}

void Camera::setCapture(std::shared_ptr<Capture> capture)
{
    m_capture = capture;
}

FBError Camera::startTracking()
{
    if (!m_capture)
    {
        std::cerr << "No capture device to start tracking" << std::endl;
        return FBError::NO_CAPTURE_DEVICE;
    }

    return m_capture->startTracking();
}

FBError Camera::stopTracking()
{
    if (!m_capture)
    {
        std::cerr << "No capture device to stop tracking" << std::endl;
        return FBError::NO_CAPTURE_DEVICE;
    }

    return m_capture->stopTracking();
}

FBError Camera::startPreview()
{
    if (!m_capture)
    {
        std::cerr << "No capture device to start preview" << std::endl;
        return FBError::NO_CAPTURE_DEVICE;
    }

    return m_capture->startPreview();
}

FBError Camera::stopPreview()
{
    if (!m_capture)
    {
        std::cerr << "No capture device to stop preview" << std::endl;
        return FBError::NO_CAPTURE_DEVICE;
    }

    return m_capture->stopPreview();
}

FBError Camera::onUpdate(float dt)
{
    if (m_capture != nullptr)
    {
        CHECK_ERRORS(m_capture->update(dt));
    }

    return FBError::OK;
}
