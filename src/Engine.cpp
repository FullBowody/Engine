#include "Engine.hpp"
#include <iostream>
#include "Plugins/PluginProvider.hpp"

Engine::Engine()
{
    
}

Engine::~Engine()
{
    
}

Camera* Engine::createCamera(std::string plugin)
{
    PluginDescriptor descriptor = PluginProvider::getInstance().getPlugin(plugin);
    if (descriptor.getType() != PluginType::CAMERA)
    {
        std::cerr << "Invalid plugin name: " << plugin << std::endl;
        return nullptr;
    }

    PluginHandle<CameraPlugin>* handle = descriptor.createHandle<CameraPlugin>();
    cameras.push_back(handle);
    return handle->getPlugin();
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
        if (cameras.at(i)->getPlugin() == camera)
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
    return cameras.at(index)->getPlugin();
}

std::vector<Camera*> Engine::getCameras()
{
    std::vector<Camera*> result;
    for (auto camera : cameras)
        result.push_back(camera->getPlugin());
    return result;
}

int Engine::start()
{
    return 0;
}

int Engine::update(float dt)
{
    for (auto camera : cameras)
    {
        int res = camera->getPlugin()->update(dt);
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
