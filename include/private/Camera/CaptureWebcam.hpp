#include <iostream>
#include <opencv2/opencv.hpp>
#include "Camera/Capture.hpp"

class CaptureWebcam: public Capture
{
private:
    cv::VideoCapture cap;
    
public:
    CaptureWebcam(int deviceId);
    ~CaptureWebcam();

    int update(float dt);
};
