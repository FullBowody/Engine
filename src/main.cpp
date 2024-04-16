#include "Engine.hpp"

#ifdef _WIN32
#define DLLExport __declspec(dllexport)
#else
#define DLLExport
#endif

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
