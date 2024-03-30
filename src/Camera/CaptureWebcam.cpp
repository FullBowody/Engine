#include "Camera/CaptureWebcam.hpp"

CaptureWebcam::CaptureWebcam(int deviceId)
{
    ready = cap.open(deviceId);
}

CaptureWebcam::~CaptureWebcam()
{
    
}

int CaptureWebcam::update(float dt)
{
    if (!ready) return 1;

    cv::Mat frame;
    cap >> frame;
    std::cout << "Frame: " << frame.cols << "x" << frame.rows << " - empty = " << frame.empty() << std::endl;
    if (frame.empty())
        return 0;

    std::cout << "Dispatching event" << std::endl;
    dispatchEvent(CameraFrameEvent(Frame(
        frame.data,
        frame.cols,
        frame.rows,
        frame.channels()
    )));
    return 0;
}
