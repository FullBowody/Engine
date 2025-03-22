#include "Structs/CaptureInfo.hpp"
#include <ostream>

CaptureInfo::CaptureInfo()
    : width(0), height(0), focal_length(0.0f), distortion(0.0f)
{

}

CaptureInfo::CaptureInfo(int width, int height, float focal_length, float distortion)
    : width(width), height(height), focal_length(focal_length), distortion(distortion)
{

}

CaptureInfo::~CaptureInfo()
{

}

std::ostream& operator<<(std::ostream& os, const CaptureInfo& infos)
{
    os << "CaptureInfo(width=" << infos.width << ", height=" << infos.height << ", focal_length=" << infos.focal_length << ", distortion=" << infos.distortion << ")";
    return os;
}

int CaptureInfo::getWidth() const
{
    return width;
}

int CaptureInfo::getHeight() const
{
    return height;
}

float CaptureInfo::getFocalLength() const
{
    return focal_length;
}

float CaptureInfo::getDistortion() const
{
    return distortion;
}
