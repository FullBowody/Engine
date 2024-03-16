#include "Engine.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Debug.hpp"

Engine::Engine()
{
    createCamera();
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

int Engine::destroyCamera(Camera* camera)
{
    for (int i = 0; i < cameras.size(); i++)
    {
        if (cameras[i] == camera)
        {
            cameras.erase(cameras.begin() + i);
            delete camera;
            return 0;
        }
    }
    return -1;
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
    return 0;
}
