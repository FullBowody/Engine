#include <napi.h>

Napi::String Ping(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    std::string res = "pong";
    return Napi::String::New(env, res);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "ping"),
        Napi::Function::New(env, Ping)
    );

    return exports;
}

NODE_API_MODULE(fullbowody, Init);