#include <napi.h>
#include "extensions/ExtensionServer.hpp"
#include "./json/json11.hpp"

Napi::Value Extensions_Start(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    new ExtensionServer();
    bool res = ExtensionServer::getInstance()->start();

    return Napi::Boolean::New(env, res);
}

Napi::Value Extensions_Stop(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    bool res = ExtensionServer::getInstance()->stop();

    return Napi::Boolean::New(env, res);
}

Napi::Value Extensions_GetState(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    State res = ExtensionServer::getInstance()->getState();

    return Napi::Number::New(env, res);
}

Napi::ThreadSafeFunction tsfn;
void __ExecuteExtensionUpdateCallback()
{
    tsfn.BlockingCall([&](Napi::Env env, Napi::Function jsCallback) {
        jsCallback.Call({});
    });
}

Napi::Value Extensions_OnExtensionUpdate(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Napi::Function cb = info[0].As<Napi::Function>();
    tsfn = Napi::ThreadSafeFunction::New(env, cb, "ExtensionUpdate", 0, 1);

    ExtensionServer::getInstance()->onExtensionUpdate(new VoidCallback(__ExecuteExtensionUpdateCallback));

    return Napi::Boolean::New(env, true);
}

Napi::Value Extensions_GetExtensions(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    std::vector<Extension*> extensions = ExtensionServer::getInstance()->getExtensions();

    std::string res = "[";
    int size = extensions.size();
    for (int i = 0; i < size; i++)
    {
        res += extensions[i]->toJSON();
        if (i < size - 1) res += ",";
    }
    res += "]";
    
    return Napi::String::New(env, res);
}