#include <chrono>
#include <string>
#include <opencv2/opencv.hpp>
#include "Camera/Capture.hpp"

class CaptureStream: public Capture
{
private:
    cv::VideoCapture cap;
    bool ready;
    std::chrono::milliseconds lastFrameTime;
    
public:
    CaptureStream(std::string url);
    ~CaptureStream();

    int update(float dt);
};
