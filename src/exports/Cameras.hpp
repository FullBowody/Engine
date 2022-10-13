#include <napi.h>
#include <vector>
#include "./common/common.hpp"
#include "cameras/CameraManager.hpp"
#include "./json/json11.hpp"

Napi::Value Cameras_GetDevices(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    int count = Camera::GetDeviceCount();
    std::vector<DeviceInfo> devices(count);
    std::string json = "[";
    for (int i = 0; i < count; i++) {
        devices[i].name = Camera::GetDeviceName(i);
        devices[i].id = i;
        json += devices[i].toJSON();
        if (i < count - 1) json += ",";
    }
    json += "]";

    return Napi::String::New(env, json);
}

Napi::Value Cameras_GetCameras(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    std::vector<Camera*> cameras = CameraManager::getInstance()->getCameras();
    std::string json = "[";
    for (auto camera : cameras) {
        json += std::to_string(camera->getId());
        if (camera != cameras.back()) json += ",";
    }
    json += "]";
    return Napi::String::New(env, json);
}

Napi::Value Cameras_GetCamera(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    int id = info[0].As<Napi::Number>().Int32Value();
    Camera* camera = CameraManager::getInstance()->getCamera(id);
    if (camera == nullptr) return Napi::String::New(env, "null");
    return Napi::String::New(env, camera->toJSON());
}

Napi::Value Cameras_SetCameraInput(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    int id = info[0].As<Napi::Number>().Int32Value();
    std::string input = info[1].As<Napi::String>();

    Camera* cam = CameraManager::getInstance()->getCamera(id);
    if (cam == nullptr)
        return Napi::Boolean::New(env, false);
    
    return Napi::Boolean::New(env, cam->setInput(input));
}

Napi::Value Cameras_StartCamera(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    int id = info[0].As<Napi::Number>().Int32Value();
    
    Camera* cam = CameraManager::getInstance()->getCamera(id);
    if (cam == nullptr)
        return Napi::Boolean::New(env, false);

    if (!cam->startRecording())
        return Napi::Boolean::New(env, false);
    
    return Napi::Boolean::New(env, true);
}

Napi::Value Cameras_StopCamera(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    int id = info[0].As<Napi::Number>().Int32Value();
    
    Camera* cam = CameraManager::getInstance()->getCamera(id);
    if (cam == nullptr)
        return Napi::Boolean::New(env, false);

    if (!cam->stopRecording())
        return Napi::Boolean::New(env, false);

    return Napi::Boolean::New(env, true);
}

Napi::Value Cameras_GetCameraData(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    int id = info[0].As<Napi::Number>().Int32Value();

    Camera* cam = CameraManager::getInstance()->getCamera(id);
    if (cam == nullptr)
        return Napi::String::New(env, "");
    
    return Napi::String::New(env, cam->getData());
}

Napi::Value Cameras_AddCamera(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    bool res = CameraManager::getInstance()->addCamera(new Camera());

    return Napi::Boolean::New(env, res);
}

Napi::Value Cameras_RemoveCamera(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    int id = info[0].As<Napi::Number>().Int32Value();
    bool res = CameraManager::getInstance()->removeCamera(id);

    return Napi::Boolean::New(env, res);
}

Napi::Value Cameras_GetLastError(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    int id = info[0].As<Napi::Number>().Int32Value();
    if (id < 0)
        return Napi::String::New(env, CameraManager::getInstance()->getLastError());
    
    Camera* cam = CameraManager::getInstance()->getCamera(id);
    if (cam == nullptr)
        return Napi::String::New(env, "");

    return Napi::String::New(env, cam->getLastError());
}