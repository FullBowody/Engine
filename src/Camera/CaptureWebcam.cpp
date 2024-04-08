#include "Camera/CaptureWebcam.hpp"

CaptureWebcam::CaptureWebcam(int deviceId)
{
#ifdef _WIN32
    ready = cap.open(deviceId, cv::CAP_DSHOW);
#else
    ready = cap.open(deviceId);
#endif
}

CaptureWebcam::~CaptureWebcam()
{
    
}

int CaptureWebcam::update(float dt)
{
    if (!ready) return 1;

    cv::Mat mat;
    cap >> mat;
    if (mat.empty())
        return 0;

    frame = Frame(
        mat.data,
        mat.cols,
        mat.rows,
        mat.channels()
    );
    dispatchEvent(CameraFrameEvent(frame));
    return 0;
}

const Frame& CaptureWebcam::getFrame() const
{
    return frame;
}
