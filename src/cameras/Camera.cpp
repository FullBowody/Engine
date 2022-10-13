#include "camera.hpp"
#include <string>
#include "../json/json11.hpp"

int Camera::_device_count = 0;
int cam_counter = 1;

// TODO : change for something better
int Camera::_generate_id() {
    return cam_counter++;
}

std::string DeviceInfo::toJSON()
{
    json11::Json obj = json11::Json::object{
        { "name", name },
        { "id", id }
    };
    return obj.dump();
}

std::string Camera::GetDeviceName(int index)
{
    cv::VideoCapture cap(index);
    return cap.getBackendName();
}

void Camera::_update_device_count()
{
    Camera::_device_count = 0;
    cv::VideoCapture cam;
    while (true)
    {
        if (!cam.open(Camera::_device_count, cv::CAP_DSHOW)) // Windows only with CAP_DSHOW
            break;
        Camera::_device_count++;
    }
}

int Camera::GetDeviceCount()
{
    if (Camera::_device_count == 0)
        Camera::_update_device_count();
    return Camera::_device_count;
}

bool Camera::_open_index(int index)
{
    if (this->state != STATE_STOPPED) return false;

    if (index < 0 || index >= Camera::GetDeviceCount()) {
        this->state = STATE_ERROR;
        this->lastError = "Invalid device index (" + std::to_string(index) + ")";
        return false;
    }

    if (!this->cap.open(index, cv::CAP_DSHOW)) { // Windows only with CAP_DSHOW
        this->state = STATE_ERROR;
        this->lastError = "Failed to open device (" + std::to_string(index) + ")";
        return false;
    }
    return true;
}

bool Camera::_open_url(std::string url)
{
    if (this->state != STATE_STOPPED) false;

    if (!this->cap.open(url, cv::CAP_DSHOW)) {
        this->state = STATE_ERROR;
        this->lastError = "Failed to open stream at "+url;
        return false;
    }
    return true;
}

Camera::Camera()
{
    this->id = Camera::_generate_id();
}

Camera::Camera(std::string input)
{
    this->id = Camera::_generate_id();
    setInput(input);
}

bool Camera::setInput(std::string input)
{
    if (state == STATE_RUNNING)
    {
        if (!this->stopRecording()) return false;
        this->input = input;
        if (!this->startRecording()) return false;
    }
    else this->input = input;
    
    return true;
}

bool Camera::startRecording()
{
    if (this->state == STATE_ERROR) return false;
    if (this->state == STATE_RUNNING) return true;

    bool res = false;
    int index = std::stoi(this->input);;
    if (index < 0) res = this->_open_url(this->input);
    else           res = this->_open_index(index);
    if (!res) return false;

    this->state = STATE_RUNNING;
    return true;
}

bool Camera::stopRecording()
{
    if (this->state == STATE_ERROR) return false;
    if (this->state == STATE_STOPPED) return true;

    this->cap.release();
    this->state = STATE_STOPPED;
    return true;
}

void Camera::_capture_frame()
{
    this->cap >> this->currentFrame;
    if (this->currentFrame.empty())
    {
        this->state = STATE_ERROR;
        this->lastError = "Failed to read device frame";
    }
}

cv::Mat Camera::getCurrentFrame()
{
    return this->currentFrame;
}

std::string Camera::getData()
{
    if (state != STATE_RUNNING) return "";
    std::vector<uchar> buf;
    if (!cv::imencode(".jpg", currentFrame, buf))
        return "";
    std::string res = base64_encode(buf.data(), buf.size());
    return res;
}

State Camera::getState()
{
    return this->state;
}

std::string Camera::getLastError()
{
    return this->lastError;
}

std::string Camera::getName()
{
    return this->name;
}

int Camera::getId()
{
    return this->id;
}

std::string Camera::getInput()
{
    return this->input;
}

std::string Camera::toJSON()
{
    json11::Json obj = json11::Json::object{
        { "name", this->name },
        { "id", this->id },
        { "input", this->input },
        { "state", this->state },
        { "lastError", this->lastError }
    };
    return obj.dump();
}

void Camera::update(float dt) {
    if (this->state == STATE_RUNNING) {
        this->frame_timelapse += dt;
        if (this->frame_timelapse > CAMERA_UPDATE_LAPSE)
        {
            this->frame_timelapse = 0.f;
            this->_capture_frame();
        }
    }
}