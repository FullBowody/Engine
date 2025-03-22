#pragma once
#include <ostream>
#include "utils.hpp"

class ENGINE_API CaptureInfo
{
private:
    int width;
    int height;
    float focal_length;
    float distortion;

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
