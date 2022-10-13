#include <napi.h>
#include "../Engine.hpp"

Napi::Value Engine_Start(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Engine::start();

    return Napi::Boolean::New(env, true);
}

Napi::Value Engine_Update(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    float dt = info[0].As<Napi::Number>().FloatValue();
    Engine::update(dt);

    return Napi::Boolean::New(env, true);
}

Napi::Value Engine_Stop(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Engine::stop();

    return Napi::Boolean::New(env, true);
}