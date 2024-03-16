#include "Camera/CaptureStream.hpp"

CaptureStream::CaptureStream(std::string url)
{
    ready = cap.open(url);
}

CaptureStream::~CaptureStream()
{
    
}

int CaptureStream::update(float dt)
{
    if (!ready) return 1;

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
