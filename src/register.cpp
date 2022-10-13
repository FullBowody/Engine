#include <napi.h>
#include "./exports/Extensions.hpp"
#include "./exports/Cameras.hpp"
#include "./exports/Engine.hpp"

void registerFunction(Napi::Object exports, Napi::Env env, std::string name, Napi::Value (*function)(const Napi::CallbackInfo&))
{
    exports.Set(Napi::String::New(env, name), Napi::Function::New(env, function));
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    registerFunction(exports, env, "engine_start", Engine_Start);
    registerFunction(exports, env, "engine_update", Engine_Update);
    registerFunction(exports, env, "engine_stop", Engine_Stop);

    registerFunction(exports, env, "extensions_start", Extensions_Start);
    registerFunction(exports, env, "extensions_stop", Extensions_Stop);
    registerFunction(exports, env, "extensions_getIp", Extensions_GetIp);
    registerFunction(exports, env, "extensions_getPort", Extensions_GetPort);
    registerFunction(exports, env, "extensions_getState", Extensions_GetState);
    registerFunction(exports, env, "extensions_getLastError", Extensions_GetLastError);
    registerFunction(exports, env, "extensions_getExtensions", Extensions_GetExtensions);

    registerFunction(exports, env, "cameras_getDevices", Cameras_GetDevices);
    registerFunction(exports, env, "cameras_getCameras", Cameras_GetCameras);
    registerFunction(exports, env, "cameras_getCamera", Cameras_GetCamera);
    registerFunction(exports, env, "cameras_setCameraInput", Cameras_SetCameraInput);
    registerFunction(exports, env, "cameras_startCamera", Cameras_StartCamera);
    registerFunction(exports, env, "cameras_stopCamera", Cameras_StopCamera);
    registerFunction(exports, env, "cameras_getCameraData", Cameras_GetCameraData);
    registerFunction(exports, env, "cameras_addCamera", Cameras_AddCamera);
    registerFunction(exports, env, "cameras_removeCamera", Cameras_RemoveCamera);
    registerFunction(exports, env, "cameras_getLastError", Cameras_GetLastError);

    return exports;
}

NODE_API_MODULE(FullBowody, Init);