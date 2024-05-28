#include "Engine.hpp"

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
