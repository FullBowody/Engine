#include "../common/common.hpp"
#include <vector>
#include <opencv2/opencv.hpp>

struct DeviceInfo {
    std::string name = "";
    int id = -1;
    std::string toJSON();
};

class Camera {
private:
    static int _device_count;
    static void _update_device_count();
    static int _generate_id();

    int id = -1;
    std::string name = "";
    std::string input = "";
    std::string lastError = "";
    State state = STATE_STOPPED;
    float frame_timelapse = 0.f;

    cv::VideoCapture cap;
    cv::Mat currentFrame;

    bool _open_index(int index);
    bool _open_url(std::string url);
    void _capture_frame();

public:
    static std::string GetDeviceName(int index);
    static int GetDeviceCount();

    Camera();
    Camera(std::string input);

    bool setInput(std::string input);
    bool startRecording();
    bool stopRecording();
    
    int getId();
    State getState();
    cv::Mat getCurrentFrame();
    std::string getData();
    std::string getInput();
    std::string getName();
    std::string getLastError();

    std::string toJSON();
    void update(float dt);
};