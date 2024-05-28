#include "Engine.hpp"

extern "C"
{
    /*DLLExport*/ __declspec(dllexport) Engine* createEngine()
    {
        return new Engine();
    }

    /*DLLExport*/ __declspec(dllexport) void destroyEngine(Engine* e)
    {
        delete e;
    }
}
