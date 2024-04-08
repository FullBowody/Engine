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

const Frame& CaptureStream::getFrame() const
{
    return frame;
}
