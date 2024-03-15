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
    
    std::cout << "Creating frame of size " << frame.cols << "x" << frame.rows << " from " << this <<std::endl;

    Frame f(
        frame.data,
        frame.cols,
        frame.rows
    );
    CameraFrameEvent ev(f);
    dispatchEvent(ev);

    std::cout << "Done updating, f = " << &f << " ev = " << &ev << " ev.data = " << &(ev.data) << " ev.data.frame" << &(ev.data.frame) << std::endl;
    return 0;
}
