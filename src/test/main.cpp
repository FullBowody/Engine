#include <iostream>
#include <thread>
#include <fstream>
#include "EngineLoader.hpp"
#include "Plugins/PluginHandle.hpp"
#include "Camera/Capture.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define LOG(x) std::cout <<  "[LOG] " << x << std::endl
#define ERR(x) std::cout << "[ERR] " << x << std::endl

std::string str(PluginType type) {
    switch (type) {
        case PluginType::CAPTURE: return "CAPTURE";
        case PluginType::UNKNOWN: return "UNKNOWN";
        default: return "INVALID";
    }
}

int main(int argc, char const *argv[])
{
    LOG("Creating EngineLoader ...");
    EngineLoader loader;
    LOG("Creating Engine ...");
    Engine* engine = loader.createEngine();
    if (engine == nullptr)
    {
        ERR("Failed to create Engine!");
        return 1;
    }

    auto& plugins = engine->getPluginProvider().getPlugins();
    LOG("Plugins (" << plugins.size() << "):");
    for (auto& plugin : plugins)
    {
        LOG("  - [" + str(plugin.getType()) + "] " + plugin.getName() + " (" + plugin.getVersion() + ") - by " + plugin.getAuthor());
    }

    std::weak_ptr<Marker> marker = engine->createMarker();
    marker.lock()->setId(0);

    std::weak_ptr<Camera> camera = engine->createCamera();
    camera.lock()->setName("testCam");
    
    if (plugins.size() > 0 && plugins[0].getType() == PluginType::CAPTURE)
    {
        LOG("Setting camera capture to " + plugins[0].getName() + " ...");
        PluginHandle<Capture>* capturePlugin = plugins[0].createHandle<Capture>();
        if (capturePlugin->getPlugin() == nullptr)
        {
            ERR("Failed to create Capture plugin!");
        }
        else
        {
            LOG("Capture plugin created, using it ...");
            camera.lock()->useCapturePlugin(capturePlugin);
            camera.lock()->startPreview();

            LOG("Capture parameters:");
            for (auto& param : capturePlugin->getPlugin()->getParameters())
            {
                LOG(" - " << param->getName());
            }
            capturePlugin->getPlugin()->getParameter("index")->setValue(0);
            capturePlugin->getPlugin()->getParameter("model")->setValue("thunder");
        }
    }
    else
    {
        ERR("No capture plugin found!");
    }

    LOG("Launching camera scene detection ...");
    {
        FBError err = camera.lock()->estimatePoseFromScene(engine->getScene(), [](const FBError& err){
            if (err) std::cout << "Error during scene detection" << std::endl;
            else std::cout << "Scene detection completed!" << std::endl;
        });
        if (err)
        {
            ERR("Failed to launch scene detection!");
            return 1;
        }
    }

    LOG("Starting tracking ...");
    FBError err = engine->startTracking();
    if (err)
    {
        ERR("Failed to start tracking!");
        return 1;
    }
    
    for (size_t i = 0; i < 100; i++)
    {
        std::cout << "Update " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        engine->update(0.03f);
    }
        

    LOG("Dumping camera image on disk ...");
    int size;
    unsigned char* data = camera.lock()->getCapture()->getImage().encodeJPG(80, &size);
    if (size == 0)
    {
        ERR("Failed to encode image!");
    }
    else
    {
        std::ofstream file("camera.jpg", std::ios::binary);
        file.write((char*) data, size);
        file.close();
        delete[] data;
    }
    
    LOG("Destroying Engine ...");
    loader.destroyEngine(engine);
    std::cout << "Goodbye!" << std::endl;
    return 0;
}
