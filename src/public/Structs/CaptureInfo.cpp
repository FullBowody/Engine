#include "Structs/CaptureInfo.hpp"
#include <ostream>

CaptureInfo::CaptureInfo()
    : m_width(0), m_height(0), m_focal_length(0.0f), m_distortion(0.0f)
{

}

CaptureInfo::CaptureInfo(int width, int height, float focal_length, float distortion)
    : m_width(width), m_height(height), m_focal_length(focal_length), m_distortion(distortion)
{

}

CaptureInfo::~CaptureInfo()
{

}

std::ostream& operator<<(std::ostream& os, const CaptureInfo& infos)
{
    os << "CaptureInfo(width=" << infos.m_width << ", height=" << infos.m_height << ", focal_length=" << infos.m_focal_length << ", distortion=" << infos.m_distortion << ")";
    return os;
}

int CaptureInfo::getWidth() const
{
    return m_width;
}

int CaptureInfo::getHeight() const
{
    return m_height;
}

float CaptureInfo::getFocalLength() const
{
    return m_focal_length;
}

float CaptureInfo::getDistortion() const
{
    return m_distortion;
}
