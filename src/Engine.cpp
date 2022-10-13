#include "Engine.hpp"
#include "./extensions/ExtensionServer.hpp"
#include "./cameras/CameraManager.hpp"

void Engine::start()
{
    ExtensionServer::getInstance();
    CameraManager::getInstance();
}

void Engine::update(float dt) {
    ExtensionServer::getInstance()->update(dt);
    CameraManager::getInstance()->update(dt);
}

void Engine::stop() {
    delete ExtensionServer::getInstance();
    delete CameraManager::getInstance();
}