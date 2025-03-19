#include "Camera/Camera.hpp"

Camera::Camera()
{
    m_capture = nullptr;
}

Camera::Camera(Capture* capture)
{
    m_capture = capture;
}

Camera::Camera(const Camera& camera)
{
    // Copy constructor
    m_capture = camera.m_capture;
}

virtual Camera::~Camera()
{
    // Destructor
    delete m_capture;
}

Camera& Camera::operator=(const Camera& other)
{
    return *this;
}

bool Camera::operator==(const Camera& other) const
{
    return Identifiable::operator==(other) && m_capture == other.m_capture;
}

bool Camera::operator!=(const Camera& other) const
{
    return Identifiable::operator!=(other) || m_capture != other.m_capture;
}

friend std::ostream& Camera::operator<<(std::ostream& os, const Camera& camera)
{
    os << "Camera(" << camera.m_name << ", capture=" << camera.m_capture << ")";
    return os;
}

virtual const Capture* Camera::getCapture() const
{
    return m_capture;
}

virtual void Camera::setCapture(Capture* capture)
{
    if (m_capture != nullptr)
    {
        delete m_capture;
    }
    m_capture = capture;
}

virtual FBError Camera::onUpdate(float dt)
{
    // TODO : Implement
    return FBError::OK;
}
