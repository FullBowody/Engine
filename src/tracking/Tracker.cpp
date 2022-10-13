#include "Tracker.hpp"
#include "../body/BodyJoint.hpp"

Tracker::Tracker()
{
    
}

Tracker::~Tracker()
{
    
}

bool Tracker::createChild()
{
    return this->ipc.createChild();
}

bool Tracker::deleteChild()
{
    return this->ipc.deleteChild();
}

void Tracker::processFrame(cv::Mat frame)
{
    std::vector<unsigned char> data;
    cv::imencode(".jpg", frame, data); // TODO : determine best way to encode image
    this->ipc.send(data);
}

void Tracker::attachCamera(Camera* camera)
{
    this->camera = camera;
}

void Tracker::update(float dt)
{
    this->updateTimer += dt;
    if (this->updateTimer < TRACKER_UPDATE_LAPSE) return;
    this->updateTimer = 0.f;

    if (this->camera == nullptr) return;

    if (this->camera->getState() == STATE_RUNNING)
    {
        this->processFrame(this->camera->getCurrentFrame());
    }

    if (this->ipc.isDataAvailable())
    {
        std::vector<unsigned char> data = this->ipc.getData();
        unsigned int length = data.size();
        unsigned int cursor = 0;
        size_t shift_joint = sizeof(TrackerJoint);

        this->trackedJoints.clear();
        while (cursor < length)
        {
            if (cursor + shift_joint > length) break;

            TrackerJoint joint;
            memcpy(&joint, &data[cursor], shift_joint);
            this->trackedJoints.push_back(joint);
            cursor += shift_joint;
        }
    }
}