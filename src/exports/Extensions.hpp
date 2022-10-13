#include <napi.h>
#include "extensions/ExtensionServer.hpp"
#include "./json/json11.hpp"

Napi::Value Extensions_Start(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    bool res =  ExtensionServer::getInstance()->start();

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

Napi::Value Extensions_GetIp(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    std::string res = ExtensionServer::getInstance()->getIp();
    
    return Napi::String::New(env, res);
}

Napi::Value Extensions_GetPort(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Port res = ExtensionServer::getInstance()->getPort();
    
    return Napi::Number::New(env, res);
}

Napi::Value Extensions_GetLastError(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    std::string res = ExtensionServer::getInstance()->getLastError();
    
    return Napi::String::New(env, res);
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