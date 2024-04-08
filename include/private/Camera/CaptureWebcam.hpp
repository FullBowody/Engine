#include <opencv2/opencv.hpp>
#include "Camera/Capture.hpp"

class CaptureWebcam: public Capture
{
private:
    cv::VideoCapture cap;
    bool ready;
    
public:
    CaptureWebcam(int deviceId);
    ~CaptureWebcam();

    int update(float dt);
    const Frame& getFrame() const;
};
