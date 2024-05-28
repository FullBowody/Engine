// #define BUILDING_DLL
#include "Engine.hpp"

#define DLLExport __declspec(dllexport)

extern "C"
{
    DLLExport Engine* createEngine()
    {
        return new Engine();
    }

    DLLExport void destroyEngine(Engine* e)
    {
        delete e;
    }
}
