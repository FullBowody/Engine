#pragma once
#include <iostream>
#include "utils.hpp"

class DLLExport CaptureInfo
{
private:
    int m_width;
    int m_height;
    float m_focal_length;
    float m_distortion;

public:
    CaptureInfo();
    CaptureInfo(int width, int height, float focal_length, float distortion);
    virtual ~CaptureInfo();

    CaptureInfo& operator=(const CaptureInfo& other);
    bool operator==(const CaptureInfo& other) const;
    bool operator!=(const CaptureInfo& other) const;
    friend std::ostream& operator<<(std::ostream& os, const CaptureInfo& infos);

    int getWidth() const;
    int getHeight() const;
    float getFocalLength() const;
    float getDistortion() const;
};

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

CaptureInfo& CaptureInfo::operator=(const CaptureInfo& other)
{
    m_width = other.m_width;
    m_height = other.m_height;
    m_focal_length = other.m_focal_length;
    m_distortion = other.m_distortion;

    return *this;
}

bool CaptureInfo::operator==(const CaptureInfo& other) const
{
    return m_width == other.m_width && m_height == other.m_height && m_focal_length == other.m_focal_length && m_distortion == other.m_distortion;
}

bool CaptureInfo::operator!=(const CaptureInfo& other) const
{
    return !(*this == other);
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
