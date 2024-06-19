#include "Engine.hpp"
#include <iostream>
#include "utils.hpp"
#include "path.hpp"
#include "Processing/FilterValues.hpp"
#include "Processing/ScenePoseResolver.hpp"

Engine::Engine()
{
    
}

Engine::~Engine()
{
    
}

void Engine::setEngineCWD(std::string dirpath)
{
    pluginProvider.setPluginsFolder(Path::Combine(dirpath, "plugins"));
}

Scene& Engine::getScene()
{
    return scene;
}

PluginProvider& Engine::getPluginProvider()
{
    return pluginProvider;
}

Camera* Engine::createCamera(std::string plugin)
{
    PluginDescriptor descriptor = pluginProvider.getPlugin(plugin);
    if (descriptor.getType() != PluginType::CAMERA)
    {
        std::cerr << "Invalid plugin name: " << plugin << std::endl;
        return nullptr;
    }

    PluginHandle<CameraPlugin>* handle = descriptor.createHandle<CameraPlugin>();
    handle->getPlugin()->setId(Identifiable::getNewId());
    cameras.push_back(handle);
    return handle->getPlugin();
}

bool Engine::destroyCamera(int id)
{
    for (int i = 0; i < cameras.size(); i++)
    {
        if (cameras.at(i)->getPlugin()->getId() == id)
        {
            delete cameras.at(i);
            cameras.erase(cameras.begin() + i);
            cameras.shrink_to_fit();
            return true;
        }
    }
    return false;
}

Camera* Engine::getCamera(int id)
{
    for (auto camera : cameras)
    {
        if (camera->getPlugin()->getId() == id)
            return camera->getPlugin();
    }
    return nullptr;
}

std::vector<Camera*> Engine::getCameras()
{
    std::vector<Camera*> result;
    for (auto camera : cameras)
        result.push_back(camera->getPlugin());
    return result;
}

int Engine::startTracking()
{
    for (auto camera : cameras)
        CHECK_ERRORS(camera->getPlugin()->startTracking())
    return 0;
}

int Engine::stopTracking()
{
    for (auto camera : cameras)
        CHECK_ERRORS(camera->getPlugin()->stopTracking())
    return 0;
}

int Engine::start()
{
    return 0;
}

int Engine::update(float dt)
{
    for (auto camera : cameras)
    {
        CHECK_ERRORS(camera->getPlugin()->update(dt))
        // if (shouldDetectMarkers)
        {
            CHECK_ERRORS(camera->getPlugin()->detectMarkers())
            std::vector<Marker> markers = camera->getPlugin()->getDetectedMarkers();
            Pose cameraPose = ScenePoseResolver::resolvePose(this->scene, markers);
            if (!cameraPose.isNull()) camera->getPlugin()->setPose(cameraPose);
        }
    }
    return 0;
}

int Engine::stop()
{
    while (!cameras.empty())
        destroyCamera(0);
    return 0;
}
