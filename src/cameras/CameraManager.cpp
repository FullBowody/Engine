#include "CameraManager.hpp"

CameraManager* CameraManager::instance = nullptr;

CameraManager::CameraManager()
{
    if (instance != nullptr)
        delete instance;
    instance = this;
}

CameraManager* CameraManager::getInstance()
{
    if (instance == nullptr)
        new CameraManager();
    return instance;
}

Camera* CameraManager::getCamera(int id)
{
    for (Camera* camera : cameras)
        if (camera->getId() == id)
            return camera;
    return nullptr;
}

bool CameraManager::addCamera(Camera* camera)
{
    if (getCamera(camera->getId()) != nullptr)
    {
        this->lastError = "Camera with id " + std::to_string(camera->getId()) + " already exists";
        return false;
    }
    cameras.push_back(camera);
    return true;
}

bool CameraManager::removeCamera(int id)
{
    for(auto it = cameras.begin(); it != cameras.end(); ++it)
        if ((*it)->getId() == id)
        {
            if (!(*it)->stopRecording())
            {
                // TODO: IDK If we should log the error or not, so it's commented out for now
                // this->lastError = "Failed to stop camera recording";
                // return false;
            }
            cameras.erase(it);
            return true;
        }

    this->lastError = "Camera (" + std::to_string(id) + ") not found";
    return false;
}

std::vector<Camera*> CameraManager::getCameras()
{
    return cameras;
}

std::string CameraManager::getLastError()
{
    std::string res = this->lastError;
    this->lastError = "";
    return res;
}

void CameraManager::update(float dt)
{
    for (Camera* camera : cameras)
        camera->update(dt);
}