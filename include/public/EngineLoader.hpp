#pragma once
#include <iostream>
#include "Engine.hpp"
#include "DLLLoader.hpp"

#ifdef _WIN32
const std::string ENGINE_LIB = "./Engine.dll";
#else
const std::string ENGINE_LIB = "./libEngine.so";
#endif

class EngineLoader
{
private:
    DLLLoader* loader = nullptr;
    Engine *(*engineCreator)() = nullptr;
    void (*engineDestroyer)(Engine *) = nullptr;

    void loadEngine(std::string path)
    {
        this->loader = new DLLLoader(path);
        this->engineCreator = (Engine *(*)()) loader->resolve("createEngine");
        this->engineDestroyer = (void (*)(Engine *)) loader->resolve("destroyEngine");
    }

public:
    EngineLoader()
    {
        loadEngine(ENGINE_LIB);
    }

    EngineLoader(std::string path)
    {
        loadEngine(path + "/" + ENGINE_LIB);
    }

    ~EngineLoader()
    {
        if (this->loader) delete this->loader;
    }

    Engine* createEngine()
    {
        if (!this->engineCreator)
        {
            std::cerr << std::endl << "Error: EngineLoader::createEngine not resolved!" << std::endl;
            return nullptr;
        }

        return this->engineCreator();
    }

    void destroyEngine(Engine* e)
    {
        if (!this->engineDestroyer)
        {
            std::cerr << std::endl << "Error: EngineLoader::destroyEngine not resolved!" << std::endl;
            return;
        }

        this->engineDestroyer(e);
    }
};
