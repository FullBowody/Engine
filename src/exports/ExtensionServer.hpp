#include <napi.h>
#include <iostream>
#include "extensions/ExtensionServer.hpp"
#include "./json/json11.hpp"

Napi::Value Extensions_Start(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Napi::Function cb1 = info[0].As<Napi::Function>();
    auto tsfn_1 = Napi::ThreadSafeFunction::New(env, cb1, "resolve", 0, 1);

    Napi::Function cb2 = info[1].As<Napi::Function>();
    auto tsfn_2 = Napi::ThreadSafeFunction::New(env, cb2, "reject", 0, 1);

    Promise* p = ExtensionServer::getInstance()->start();
    p->onResolve([tsfn_1](void* c){
        tsfn_1.BlockingCall([&](Napi::Env env, Napi::Function jsCallback) {
            jsCallback.Call({});
        });
    })->onReject([tsfn_2](void* c){
        tsfn_2.BlockingCall([&](Napi::Env env, Napi::Function jsCallback) {
            jsCallback.Call({});
        });
    });

    return Napi::Boolean::New(env, true);
}

Napi::Value Extensions_Stop(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Napi::Function cb1 = info[0].As<Napi::Function>();
    auto tsfn_1 = Napi::ThreadSafeFunction::New(env, cb1, "resolve", 0, 1);

    Napi::Function cb2 = info[1].As<Napi::Function>();
    auto tsfn_2 = Napi::ThreadSafeFunction::New(env, cb2, "reject", 0, 1);

    Promise* p = ExtensionServer::getInstance()->stop();
    p->onResolve([&](void* c){
        tsfn_1.BlockingCall([&](Napi::Env env, Napi::Function jsCallback) {
            jsCallback.Call({});
        });
    })->onReject([&](void* c){
        tsfn_2.BlockingCall([&](Napi::Env env, Napi::Function jsCallback) {
            jsCallback.Call({});
        });
    });

    return Napi::Boolean::New(env, true);
}

Napi::Value Extensions_GetState(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    State res = ExtensionServer::getInstance()->getState();

    return Napi::Number::New(env, res);
}

Napi::Value Extensions_OnExtensionUpdate(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    Napi::Function cb = info[0].As<Napi::Function>();
    auto tsfn = Napi::ThreadSafeFunction::New(env, cb, "callback", 0, 1);

    ExtensionServer::getInstance()->onExtensionUpdate(new VoidCallback([tsfn](){
        tsfn.BlockingCall([&](Napi::Env env, Napi::Function jsCallback) {
            jsCallback.Call({});
        });
    }));

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