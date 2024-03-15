#include "Engine.hpp"
#include <iostream>

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
    camera->attachListener(this); // TODO : remove this (for testing only)
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
        camera->update(dt);
    }
    return 0;
}

int Engine::stop()
{
    return 0;
}

void Engine::onEvent(const CameraFrameEvent& event)  // TODO : remove this (for testing only)
{
    std::cout << "Got event of address " << &event << std::endl;
    std::cout << "Got event data of address " << &(event.data) << std::endl;
    std::cout << "Got event data frame of address : " << &(event.data.frame) << std::endl;
    // std::cout << "Frame size : " << event.data.frame.width << "x" << event.data.frame.height << std::endl;
}
