#include <chrono>
#include <opencv2/opencv.hpp>
#include "Camera/Capture.hpp"

class CaptureWebcam: public Capture
{
private:
    cv::VideoCapture cap;
    bool ready;
    std::chrono::milliseconds lastFrameTime;
    
public:
    CaptureWebcam(int deviceId);
    ~CaptureWebcam();

    int update(float dt);
};
