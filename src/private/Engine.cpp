#include "Engine.hpp"
#include <iostream>
#include <chrono>
#include "utils.hpp"
#include "path.hpp"

Engine::Engine()
{
    scene = std::make_shared<Scene>();
    skeleton = std::make_shared<Skeleton>();
    pluginProvider = std::make_shared<PluginProvider>();
    listenerServer = std::make_shared<ListenerServer>();
}

Engine::~Engine()
{
    
}

std::future<std::shared_ptr<PluginProvider>> Engine::getPluginProvider()
{
    std::promise<std::shared_ptr<PluginProvider>> promise;
    addAction([this, &promise]() {
        promise.set_value(pluginProvider);
    });
    return promise.get_future();
}

std::future<std::shared_ptr<ListenerServer>> Engine::getListenerServer()
{
    std::promise<std::shared_ptr<ListenerServer>> promise;
    addAction([this, &promise]() {
        promise.set_value(listenerServer);
    });
    return promise.get_future();
}

void Engine::setEngineCWD(std::string dirpath)
{
    addAction([this, &dirpath]() {
        pluginProvider->setPluginsFolder(Path::Combine(dirpath, "plugins"));
    });
}

std::future<std::weak_ptr<Camera>> Engine::createCamera()
{
    std::promise<std::weak_ptr<Camera>> promise;
    addAction([this, &promise]() {
        auto camera = std::make_shared<Camera>();
        cameras.push_back(camera);
        promise.set_value(camera);
    });
    return promise.get_future();
}

std::future<std::weak_ptr<Camera>> Engine::getCamera(int index)
{
    std::promise<std::weak_ptr<Camera>> promise;
    addAction([this, &promise, index]() {
        if (index < 0 || index >= cameras.size())
        {
            promise.set_value(std::weak_ptr<Camera>());
            return;
        }
        promise.set_value(cameras[index]);
    });
    return promise.get_future();
}

std::future<FBError> Engine::destroyCamera(int index)
{
    std::promise<FBError> promise;
    addAction([this, &promise, index]() {
        if (index < 0 || index >= cameras.size())
        {
            promise.set_value(FBError::NO_CAMERA);
            return;
        }
        cameras.erase(cameras.begin() + index);
        promise.set_value(FBError::OK);
    });
    return promise.get_future();
}

std::future<FBError> Engine::destroyCamera(const Camera& camera)
{
    std::promise<FBError> promise;
    addAction([this, &promise, camera]() {
        auto it = std::find_if(cameras.begin(), cameras.end(), [&camera](const std::shared_ptr<Camera>& cam) {
            return cam.get() == &camera;
        });
        if (it != cameras.end())
        {
            cameras.erase(it);
            promise.set_value(FBError::OK);
        }
        else
        {
            promise.set_value(FBError::NO_CAMERA);
        }
    });
    return promise.get_future();
}

std::future<std::reference_wrapper<std::vector<std::shared_ptr<Camera>>>> Engine::getCameras()
{
    std::promise<std::reference_wrapper<std::vector<std::shared_ptr<Camera>>>> promise;
    addAction([this, &promise]() {
        promise.set_value(std::ref(cameras));
    });
    return promise.get_future();
}

std::future<std::shared_ptr<Scene>> Engine::getScene()
{
    std::promise<std::shared_ptr<Scene>> promise;
    addAction([this, &promise]() {
        promise.set_value(scene);
    });
    return promise.get_future();
}

std::future<std::weak_ptr<Skeleton>> Engine::getSkeleton()
{
    std::promise<std::weak_ptr<Skeleton>> promise;
    addAction([this, &promise]() {
        promise.set_value(skeleton);
    });
    return promise.get_future();
}

std::future<FBError> Engine::startTracking()
{
    std::promise<FBError> promise;
    addAction([this, &promise]() {
        if (scene->getMarkerCount() == 0)
        {
            std::cerr << "No markers to start tracking" << std::endl;
            promise.set_value(FBError::NO_MARKER);
            return;
        }

        if (cameras.size() == 0)
        {
            std::cerr << "No cameras to start tracking" << std::endl;
            promise.set_value(FBError::NO_CAMERA);
            return;
        }

        for (auto& camera : cameras)
        {
            if (!camera->getCapture())
            {
                std::cerr << "Camera " << camera->getName() << " has no capture device" << std::endl;
                promise.set_value(FBError::NO_CAPTURE_DEVICE);
                return;
            }
        }

        for (auto& camera : cameras)
        {
            FBError err = camera->startTracking();
            if (err)
            {
                std::cerr << "Failed to start tracking for camera " << camera->getName() << std::endl;
                promise.set_value(err);
                return;
            }
        }

        promise.set_value(FBError::OK);
    });
    return promise.get_future();
}

std::future<FBError> Engine::stopTracking()
{
    std::promise<FBError> promise;
    addAction([this, &promise]() {
        for (auto& camera : cameras)
        {
            camera->stopTracking();
        }
        promise.set_value(FBError::OK);
    });
    return promise.get_future();
}

// running in update thread
FBError Engine::onUpdate(float dt)
{
    executeActions(); // Execute all actions in the queue
    if (shouldStop) // if shouldStop is set, exit the update loop
    {
        return FBError::OK;
    }

    for (auto& camera : cameras)
    {
        CHECK_ERRORS(camera->update(dt));
    }

    return FBError::OK;
}

FBError Engine::start()
{
    shouldStop = false;
    // TOOD : Start the listener server here instead of in the constructor

    updateThread = std::thread([this]() {
        const float TARGET_INTERVAL = 1.0f / 60.0f; // 60 FPS 
        std::clock_t startTime = std::clock();
        while (!shouldStop)
        {
            std::clock_t currentTime = std::clock();
            float deltaTime = static_cast<float>(currentTime - startTime) / CLOCKS_PER_SEC;
            startTime = currentTime;

            if (deltaTime < TARGET_INTERVAL)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((TARGET_INTERVAL - deltaTime) * 1000)));
                continue;
            }

            FBError err = onUpdate(deltaTime);
            if (err)
            {
                std::cerr << "Error during update: " << static_cast<int>(err) << std::endl;
                // shouldStop = true;
                // break;
            }
        }
    });
    return FBError::OK;
}

FBError Engine::stop()
{
    shouldStop = true;
    stopTracking();
    updateThread.join();
    return FBError::OK;
}
