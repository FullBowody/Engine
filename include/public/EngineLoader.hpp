#include <iostream>
#include "Engine.hpp"

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#ifdef _WIN32
const std::string ENGINE_LIB = "./Engine.dll";
#else
const std::string ENGINE_LIB = "./libEngine.so";
#endif

class EngineLoader
{
private:
#ifdef _WIN32
    HINSTANCE hGetProcIDDLL;
#else
    void* handle;
#endif
    Engine *(*engineCreator)() = nullptr;
    void (*engineDestroyer)(Engine *) = nullptr;

    void setLoadPath(std::string path)
    {
#ifdef _WIN32
        // add path to Engine.dll to search
        SetDllDirectoryA(path.c_str());
#else
        // set path to Engine.so
        this->path = path;
#endif
    }

    void loadEngine()
    {
#ifdef _WIN32
        // load Engine.dll
        this->hGetProcIDDLL = LoadLibraryA(ENGINE_LIB.c_str());
        if (!hGetProcIDDLL)
        {
            std::cerr << std::endl << "Error: Could not load Engine.dll library!" << std::endl;
            std::cerr << "Error code: " << GetLastError() << std::endl;
            return;
        }

        // resolve Engine class
        this->engineCreator = (Engine *(*)()) GetProcAddress(hGetProcIDDLL, "createEngine");
        this->engineDestroyer = (void (*)(Engine *)) GetProcAddress(hGetProcIDDLL, "destroyEngine");
#else
        this->path = path + "/" + ENGINE_LIB;
        this->handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!this->handle)
        {
            std::cerr << std::endl << "Error: Could not load Engine.so library!" << std::endl;
            std::cerr << "Error: " << dlerror() << std::endl;
            return;
        }

        // resolve Engine class
        this->engineCreator = (Engine *(*)()) dlsym(this->handle, "createEngine");
        this->engineDestroyer = (void (*)(Engine *)) dlsym(this->handle, "destroyEngine");
#endif

        if (!this->engineCreator || !this->engineDestroyer)
        {
            std::cerr << std::endl << "Error: Could not locate EngineLoader::createEngine and EngineLoader::destroyEngine!" << std::endl;
            return;
        }
    }

    void unloadEngine()
    {
#ifdef _WIN32
        FreeLibrary(this->hGetProcIDDLL);
#else
        dlclose(this->handle);
#endif
    }

public:
    EngineLoader()
    {
        loadEngine();
    }

    EngineLoader(std::string path)
    {
        setLoadPath(path);
        loadEngine();
    }

    ~EngineLoader()
    {
        unloadEngine();
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
