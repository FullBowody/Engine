#include <iostream>
#include <thread>
#include <chrono>
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
    std::cout << "Hello!" << std::endl;

    LOG("Creating EngineLoader ...");
    EngineLoader loader;
    LOG("Creating Engine ...");
    Engine* engine = loader.createEngine();
    if (engine == nullptr)
    {
        ERR("Failed to create Engine!");
        return 1;
    }
    
    std::cout << "Starting engine ..." << std::endl;
    engine->start();

    std::cout << "Waiting for 10 seconds ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "Done !" << std::endl;

    std::cout << "Stopping engine ..." << std::endl;
    engine->stop();
    
    LOG("Destroying Engine ...");
    loader.destroyEngine(engine);
    std::cout << "Goodbye!" << std::endl;
    return 0;
}
