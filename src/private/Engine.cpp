#include "Engine.hpp"
#include <iostream>
#include "utils.hpp"
#include "path.hpp"

Engine::Engine()
{
    
}

Engine::~Engine()
{
    
}

PluginProvider& Engine::getPluginProvider()
{
    return pluginProvider;
}

void Engine::setEngineCWD(std::string dirpath)
{
    pluginProvider.setPluginsFolder(Path::Combine(dirpath, "plugins"));
}

std::weak_ptr<Camera> Engine::createCamera()
{
    cameras.push_back(std::make_shared<Camera>());
    return cameras.back();
}

std::weak_ptr<Camera> Engine::getCamera(int index)
{
    return cameras[index];
}

void Engine::destroyCamera(int index)
{
    cameras.erase(cameras.begin() + index);
}

void Engine::destroyCamera(const Camera& camera)
{
    cameras.erase(std::remove_if(cameras.begin(), cameras.end(), [&camera](const std::shared_ptr<Camera>& cam) {
        return cam.get() == &camera;
    }), cameras.end());
}

const std::vector<std::shared_ptr<Camera>>& Engine::getCameras()
{
    return cameras;
}

std::weak_ptr<Marker> Engine::createMarker()
{
    std::shared_ptr<Marker> marker = std::make_shared<Marker>();
    scene.addMarker(marker);
    return marker;
}

std::weak_ptr<Marker> Engine::getMarker(int index)
{
    return scene.getMarker(index);
}

void Engine::destroyMarker(int index)
{
    scene.destroyMarker(index);
}

void Engine::destroyMarker(const Marker& marker)
{
    scene.destroyMarker(marker);
}

const std::vector<std::shared_ptr<Marker>>& Engine::getMarkers()
{
    return scene.getMarkers();
}

const Scene& Engine::getScene()
{
    return scene;
}

std::weak_ptr<Skeleton> Engine::getSkeleton()
{
    return skeleton;
}

FBError Engine::startTracking()
{
    if (scene.getMarkerCount() == 0)
    {
        std::cerr << "No markers to start tracking" << std::endl;
        return FBError::NO_MARKER;
    }

    if (cameras.size() == 0)
    {
        std::cerr << "No cameras to start tracking" << std::endl;
        return FBError::NO_CAMERA;
    }

    for (auto& camera : cameras)
    {
        if (!camera->getCapture())
        {
            std::cerr << "Camera " << camera->getName() << " has no capture device" << std::endl;
            return FBError::NO_CAPTURE_DEVICE;
        }
    }

    for (auto& camera : cameras)
    {
        FBError& err = camera->startTracking();
        if (err)
        {
            std::cerr << "Failed to start tracking for camera " << camera->getName() << std::endl;
            return err;
        }
    }

    return FBError::OK;
}

FBError Engine::stopTracking()
{
    for (auto& camera : cameras)
    {
        camera->stopTracking();
    }

    return FBError::OK;
}

FBError Engine::onUpdate(float dt)
{
    for (auto& camera : cameras)
    {
        CHECK_ERRORS(camera->update(dt));
    }

    return FBError::OK;
}
