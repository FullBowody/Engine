#include <iostream>
#include <windows.h>
#include "Engine.hpp"

class EngineLoader
{
private:
    HINSTANCE hGetProcIDDLL;
    Engine *(*engineCreator)();
    void (*engineDestroyer)(Engine *);

public:
    EngineLoader(std::string path)
    {
        this->hGetProcIDDLL = LoadLibraryA(path.c_str());
        if (!hGetProcIDDLL)
        {
            std::cerr << "Could not load the dynamic library" << std::endl;
            return;
        }

        // resolve Engine class
        this->engineCreator = (Engine *(*)()) GetProcAddress(hGetProcIDDLL, "createEngine");
        this->engineDestroyer = (void (*)(Engine *)) GetProcAddress(hGetProcIDDLL, "destroyEngine");

        if (!this->engineCreator || !this->engineDestroyer)
        {
            std::cerr << "Could not locate the creator and destructor functions" << std::endl;
            return;
        }
    }

    ~EngineLoader()
    {
        FreeLibrary(this->hGetProcIDDLL);
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
