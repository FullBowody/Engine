#include <iostream>
#include <thread>
#include "EngineLoader.hpp"

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
    if (engine == nullptr) {
        ERR("Failed to create Engine!");
        return 1;
    }

    auto& plugins = engine->getPluginProvider().getPlugins();
    LOG("Plugins (" << plugins.size() << "):");
    for (auto& plugin : plugins) {
        LOG("  - [" + str(plugin.getType()) + "] " + plugin.getName() + " (" + plugin.getVersion() + ") - by " + plugin.getAuthor());
    }

    std::weak_ptr<Marker> marker = engine->createMarker();
    marker.lock()->setId(0);

    std::weak_ptr<Camera> camera = engine->createCamera();
    camera.lock()->setName("testCam");
    
    if (plugins.size() > 0 && plugins[0].getType() == PluginType::CAPTURE) {
        LOG("Setting camera capture to " + plugins[0].getName() + " ...");
        // PluginCapture* capturePlugin = dynamic_cast<PluginCapture*>(plugins[0].getPlugin());
        // camera.lock()->useCapture(capturePlugin);
    } else {
        ERR("No capture plugin found!");
        return 1;
    }

    camera.lock()->setCapture(nullptr);

    LOG("Starting tracking ...");
    FBError err = engine->startTracking();
    if (err) {
        ERR("Failed to start tracking!");
        return 1;
    }

    engine->update(0.1);
    
    LOG("Destroying Engine ...");
    loader.destroyEngine(engine);
    std::cout << "Goodbye!" << std::endl;
    return 0;
}
