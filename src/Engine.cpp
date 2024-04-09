#include "Engine.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Debug.hpp"

Engine::Engine()
{
    
}

Engine::~Engine()
{
    
}

Camera* Engine::createCamera()
{
    Camera* camera = new Camera();
    cameras.push_back(camera);
    return camera;
}

bool Engine::destroyCamera(int index)
{
    if (index < 0 || index >= cameras.size())
        return false;
    delete cameras.at(index);
    cameras.erase(cameras.begin() + index);
    return true;
}

Camera* Engine::getCamera(int index)
{
    if (index < 0 || index >= cameras.size())
        return nullptr;
    return cameras.at(index);
}

const std::vector<Camera*>& Engine::getCameras()
{
    return cameras;
}

int Engine::start()
{
    return 0;
}

int Engine::update(float dt)
{
    for (auto camera : cameras)
    {
        int res = camera->update(dt);
        if (res) return res; // stop update and return error code
    }
    return 0;
}

int Engine::stop()
{
    while (!cameras.empty())
        destroyCamera(0);
    return 0;
}
