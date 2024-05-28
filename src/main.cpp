#define BUILDING_DLL
#include "Engine.hpp"

extern "C"
{
    __declspec(dllexport) Engine* createEngine()
    {
        return new Engine();
    }

    __declspec(dllexport) void destroyEngine(Engine* e)
    {
        delete e;
    }
}
