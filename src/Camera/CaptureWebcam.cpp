#include "Camera/CaptureWebcam.hpp"

CaptureWebcam::CaptureWebcam(int deviceId)
{
    cap.open(deviceId);
}

CaptureWebcam::~CaptureWebcam()
{
    
}

int CaptureWebcam::update(float dt)
{
    cv::Mat frame;
    cap >> frame;
    if (frame.empty())
        return 0;

    dispatchEvent(CameraFrameEvent(Frame(
        frame.data,
        frame.cols,
        frame.rows,
        frame.channels()
    )));
    return 0;
}
