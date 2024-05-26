#include "Engine.hpp"
#include <iostream>

Engine::Engine()
{
    
}

Engine::~Engine()
{
    
}

Camera* Engine::createCamera()
{
    Camera* camera = nullptr; // TODO : Implement plugins for different camera types
    cameras.push_back(camera);
    return camera;
}

bool Engine::destroyCamera(int index)
{
    if (index < 0 || index >= cameras.size())
        return false;
    delete cameras.at(index);
    cameras.erase(cameras.begin() + index);
    cameras.shrink_to_fit();
    return true;
}

bool Engine::destroyCamera(Camera* camera)
{
    for (int i = 0; i < cameras.size(); i++)
    {
        if (cameras.at(i) == camera)
        {
            delete camera;
            cameras.erase(cameras.begin() + i);
            cameras.shrink_to_fit();
            return true;
        }
    }
    return false;
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
