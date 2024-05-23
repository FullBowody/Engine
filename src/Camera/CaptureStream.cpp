#include "Camera/CaptureStream.hpp"

CaptureStream::CaptureStream(std::string url)
{
    ready = cap.open(url);
    if (!ready)
    {
        std::cerr << "CaptureStream: failed to open " << url << std::endl;
        return;
    }

    width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    fps = cap.get(cv::CAP_PROP_FPS);
}

CaptureStream::~CaptureStream()
{
    cap.release();
}

int CaptureStream::update(float dt)
{
    if (!ready) return 1;

    cv::Mat mat;
    cap >> mat;
    if (mat.empty())
        return 0;
        
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );
    fps = 1000.0f / (now - lastFrameTime).count();
    lastFrameTime = now;

    dispatchEvent(CameraFrameEvent(Frame(
        mat.data,
        mat.cols,
        mat.rows,
        mat.channels()
    )));
    return 0;
}
