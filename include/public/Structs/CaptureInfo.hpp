#pragma once
#include <ostream>
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

    friend std::ostream& operator<<(std::ostream& os, const CaptureInfo& infos);

    int getWidth() const;
    int getHeight() const;
    float getFocalLength() const;
    float getDistortion() const;
};
