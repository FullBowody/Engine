#include <iostream>
#include "Engine.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

class EngineLoader
{
private:
#ifdef _WIN32
    HINSTANCE hGetProcIDDLL;
#else
    void* handle;
#endif
    Engine *(*engineCreator)();
    void (*engineDestroyer)(Engine *);

public:
    EngineLoader(std::string path)
    {
#ifdef _WIN32
        this->hGetProcIDDLL = LoadLibraryA(path.c_str());
        if (!hGetProcIDDLL)
        {
            std::cerr << std::endl << "Error: Could not load Engine.dll library!" << std::endl;
            return;
        }

        // resolve Engine class
        this->engineCreator = (Engine *(*)()) GetProcAddress(hGetProcIDDLL, "createEngine");
        this->engineDestroyer = (void (*)(Engine *)) GetProcAddress(hGetProcIDDLL, "destroyEngine");
#else
        this->handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!this->handle)
        {
            std::cerr << std::endl << "Error: Could not load Engine.so library!" << std::endl;
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

    ~EngineLoader()
    {
#ifdef _WIN32
        FreeLibrary(this->hGetProcIDDLL);
#else
        dlclose(this->handle);
#endif
    }

    Engine* createEngine()
    {
        return this->engineCreator();
    }

    void destroyEngine(Engine* e)
    {
        this->engineDestroyer(e);
    }
};
