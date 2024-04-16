#include "Camera/CameraFrameEventData.hpp"

CameraFrameEventData::CameraFrameEventData(const Frame& frame)
    : frame(frame)
{
    
}

CameraFrameEventData::CameraFrameEventData(const CameraFrameEventData& data)
    : frame(data.frame)
{
    
}

CameraFrameEventData::~CameraFrameEventData()
{

}

const Frame& CameraFrameEventData::getFrame() const
{
    return frame;
}
