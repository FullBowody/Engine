#include <napi.h>
#include "./exports/ExtensionServer.hpp"

void registerFunction(Napi::Object exports, Napi::Env env, std::string name, Napi::Value (*function)(const Napi::CallbackInfo&))
{
    exports.Set(Napi::String::New(env, name), Napi::Function::New(env, function));
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    registerFunction(exports, env, "extensions_start", Extensions_Start);
    registerFunction(exports, env, "extensions_stop", Extensions_Stop);
    registerFunction(exports, env, "extensions_getState", Extensions_GetState);
    registerFunction(exports, env, "extensions_onExtensionUpdate", Extensions_OnExtensionUpdate);
    registerFunction(exports, env, "extensions_getExtensions", Extensions_GetExtensions);
    registerFunction(exports, env, "extensions_getIp", Extensions_GetIp);
    registerFunction(exports, env, "extensions_getPort", Extensions_GetPort);

    return exports;
}

NODE_API_MODULE(FullBowody, Init);