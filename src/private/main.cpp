#include "Engine.hpp"

extern "C"
{
    ENGINE_API Engine* createEngine()
    {
        return new Engine();
    }

    ENGINE_API void destroyEngine(Engine* e)
    {
        delete e;
    }
}
