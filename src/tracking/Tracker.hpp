#pragma once
#include "../common/common.hpp"
#include "../cameras/Camera.hpp"
#include "./IPC.hpp"

struct TrackerJoint
{
    unsigned short x = 0;
    unsigned short y = 0;
    unsigned short z = 0;
    unsigned char confidence = 0;
    TrackerJoint() {}
    TrackerJoint(unsigned short x, unsigned short y, unsigned short z, unsigned char confidence)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->confidence = confidence;
    }
};

class Tracker
{
private:
    Camera* camera = nullptr;
    std::vector<TrackerJoint> trackedJoints;
    float updateTimer = 0.f;
    IPC ipc;

    void processFrame(cv::Mat frame);

public:
    Tracker();
    ~Tracker();

    bool createChild();
    bool deleteChild();

    void attachCamera(Camera* camera);

    void update(float dt);
};