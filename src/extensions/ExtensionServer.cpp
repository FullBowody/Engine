#include <iostream>
#include "ExtensionServer.hpp"
#include "Network.hpp"
#include "../json/json11.hpp"

ExtensionServer* ExtensionServer::instance = nullptr;

ExtensionServer* ExtensionServer::getInstance()
{
    if (ExtensionServer::instance == nullptr)
    {
        new ExtensionServer();
    }
    return ExtensionServer::instance;
}

ExtensionServer::ExtensionServer()
{
    if (ExtensionServer::instance != nullptr)
    {
        delete ExtensionServer::instance;
    }

    state = STATE_STOPPED;
    ExtensionServer::instance = this;
}

ExtensionServer::~ExtensionServer()
{
    this->stop();
}

bool ExtensionServer::start()
{
    state = STATE_STARTING;
    Network* net = new Network();
    if (!net->setup())
    {
        lastError = net->getLastError();
        state = STATE_ERROR;
        return false;
    }

    net->onDataReceived(new TypedArgsCallback<ExtensionServer>(&ExtensionServer::_onPaquet, this));
    bool res = net->start(new VoidCallback([](){
        std::cout << "Network started on port " << DEFAULT_PORT << std::endl;
        ExtensionServer::getInstance()->state = STATE_STARTED;
    }));
    if (!res)
    {
        state = STATE_ERROR;
        lastError = "start: Failed to start network";
        return false;
    }
    return true;
}

bool ExtensionServer::stop()
{
    state = STATE_STOPPING;
    Network::getInstance()->stop();
    return true;
}

State ExtensionServer::getState()
{
    return state;
}

std::string ExtensionServer::getLastError()
{
    return lastError;
}

std::vector<Extension*> ExtensionServer::getExtensions()
{
    return extensions;
}

Extension* ExtensionServer::getExtension(std::string name)
{
    for (Extension* ext : extensions)
    {
        if (ext->getName() == name)
        {
            return ext;
        }
    }
    lastError = "getExtension: Extension " + name + " not found";
    return nullptr;
}

void ExtensionServer::onExtensionUpdate(Callback* callback)
{
    updateCallback = callback;
}

bool ExtensionServer::addExtension(Extension* ext)
{
    std::string name = ext->getName();
    if (getExtension(name) != nullptr)
    {
        lastError = "addExtension: Extension with name " + name + " already exists";
        return false;
    }
    extensions.push_back(ext);
    if (updateCallback != nullptr)
        updateCallback->call();
    return true;
}

bool ExtensionServer::removeExtension(std::string name, std::string key)
{
    for (auto it = extensions.begin(); it != extensions.end(); ++it)
    {
        if ((*it)->getName() == name)
        {
            if ((*it)->getKey() == key)
            {
                extensions.erase(it);
                if (updateCallback != nullptr)
                    updateCallback->call();
                return true;
            }
            else
            {
                lastError = "removeExtension: Invalid key";
                return false;
            }
        }
    }
    lastError = "removeExtension: Extension with name " + name + " does not exist";
    return false;
}

void ExtensionServer::_onPaquet(void* data)
{
    NetworkPacket packet = *(NetworkPacket*)data;

    if (packet.data.rfind("[ON]", 0) == 0) // New addon registering
    {
        std::string str = packet.data.substr(4);
        json11::Json json = json11::Json::parse(str, lastError);
        if (json.is_null())
        {
            std::string err = "Failed to parse addon registration JSON: " + lastError;
            // TODO : save error to display it in UI in realtime
            return;
        }

        std::string name = json["name"].string_value();
        std::string key = json["key"].string_value();
        if (name == "")
        {
            lastError = "Invalid addon registration JSON: name is empty";
            // TODO : save error to display it in UI in realtime
            return;
        }
        if (key == "")
        {
            lastError = "Invalid addon registration JSON: key is empty";
            // TODO : save error to display it in UI in realtime
            return;
        }

        addExtension(new Extension(name, key, packet.ip, packet.port));
    }

    if (packet.data.rfind("[OFF]", 0) == 0) // Addon shutting down
    {
        std::string str = packet.data.substr(5);
        json11::Json json = json11::Json::parse(str, lastError);
        if (json.is_null())
        {
            std::string err = "Failed to parse addon removal JSON: " + lastError;
            // TODO : save error to display it in UI in realtime
            return;
        }

        std::string name = json["name"].string_value();
        std::string key = json["key"].string_value();
        if (name == "")
        {
            lastError = "Invalid addon removal JSON: name is empty";
            // TODO : save error to display it in UI in realtime
            return;
        }
        if (key == "")
        {
            lastError = "Invalid addon removal JSON: key is empty";
            // TODO : save error to display it in UI in realtime
            return;
        }

        removeExtension(name, key);
    }
}