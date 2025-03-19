#include "Camera/Capture.hpp"
#include <string>
#include "Structs/Transform.hpp"
#include "Camera/Image.hpp"
#include "Structs/CaptureInfo.hpp"
#include "Structs/CaptureSkeleton.hpp"

std::string& Capture::getType() const {
    return m_type;
}

Transform& Capture::getTransform() const {
    return m_transform;
}

int Capture::getWidth() const {
    return m_width;
}

int Capture::getHeight() const {
    return m_height;
}

CaptureInfo& Capture::getInfos() const {
    return m_infos;
}

Image& Capture::getImage() const {
    return m_image;
}

CaptureSkeleton& Capture::getSkeleton() const {
    return m_skeleton;
}

Transform& Capture::calibrate() {
    return onCalibrate();
}
