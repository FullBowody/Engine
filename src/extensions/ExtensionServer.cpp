#include "ExtensionServer.hpp"
#include "../json/json11.hpp"
#include <iostream>

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

    this->state = STATE_STOPPED;
    ExtensionServer::instance = this;
}

ExtensionServer::~ExtensionServer()
{
    this->stop();
}

bool ExtensionServer::start()
{
    if (this->state == STATE_ERROR) return false;
    if (this->state == STATE_RUNNING) return true;

    if (!Network::getInstance()->setup())
    {
        this->lastError = "Failed to start network : " + Network::getInstance()->getLastError();
        this->state = STATE_ERROR;
        return false;
    }

    if (!Network::getInstance()->start())
    {
        this->state = STATE_ERROR;
        this->lastError = "Failed to start network : " + Network::getInstance()->getLastError();
        return false;
    }

    this->state = STATE_RUNNING;
    return true;
}

bool ExtensionServer::stop()
{
    if (this->state == STATE_ERROR) return false;
    if (this->state == STATE_STOPPED) return true;

    if (!Network::getInstance()->stop())
    {
        this->state = STATE_ERROR;
        this->lastError = "stop: Failed to stop network";
        return false;
    }

    return true;
}

State ExtensionServer::getState()
{
    return this->state;
}

std::string ExtensionServer::getLastError()
{
    std::string res = this->lastError;
    this->lastError = "";
    return this->lastError;
}

std::vector<Extension*> ExtensionServer::getExtensions()
{
    return this->extensions;
}

Extension* ExtensionServer::getExtension(std::string name)
{
    for (Extension* ext : this->extensions)
    {
        if (ext->getName() == name)
        {
            return ext;
        }
    }
    this->lastError = "getExtension: Extension " + name + " not found";
    return nullptr;
}

bool ExtensionServer::addExtension(Extension* ext)
{
    std::string name = ext->getName();
    if (getExtension(name) != nullptr)
    {
        this->lastError = "addExtension: Extension with name " + name + " already exists";
        return false;
    }
    this->extensions.push_back(ext);
    return true;
}

bool ExtensionServer::removeExtension(std::string name, std::string key)
{
    for (auto it = this->extensions.begin(); it != this->extensions.end(); ++it)
    {
        if ((*it)->getName() == name)
        {
            if ((*it)->getKey() == key)
            {
                this->extensions.erase(it);
                return true;
            }
            else
            {
                this->lastError = "removeExtension: Invalid key";
                return false;
            }
        }
    }
    this->lastError = "removeExtension: Extension with name " + name + " does not exist";
    return false;
}

bool ExtensionServer::_process_packet(NetworkPacket packet)
{
    if (packet.data.rfind("[ON]", 0) == 0) // New addon registering
    {
        std::string str = packet.data.substr(4);
        json11::Json json = json11::Json::parse(str, lastError);
        if (json.is_null())
        {
            this->lastError = "Failed to parse addon registration JSON: " + this->lastError;
            return false;
        }

        std::string name = json["name"].string_value();
        std::string key = json["key"].string_value();
        if (name == "")
        {
            this->lastError = "Invalid addon registration JSON: name is empty";
            return false;
        }
        if (key == "")
        {
            this->lastError = "Invalid addon registration JSON: key is empty";
            return false;
        }

        addExtension(new Extension(name, key, packet.ip, packet.port));
    }

    if (packet.data.rfind("[OFF]", 0) == 0) // Addon shutting down
    {
        std::string str = packet.data.substr(5);
        json11::Json json = json11::Json::parse(str, this->lastError);
        if (json.is_null())
        {
            this->lastError = "Failed to parse addon removal JSON: " + this->lastError;
            return false;
        }

        std::string name = json["name"].string_value();
        std::string key = json["key"].string_value();
        if (name == "")
        {
            this->lastError = "Invalid addon removal JSON: name is empty";
            return false;
        }
        if (key == "")
        {
            this->lastError = "Invalid addon removal JSON: key is empty";
            return false;
        }

        removeExtension(name, key);
    }
    return true;
}

std::string ExtensionServer::getIp()
{
    if (this->state != STATE_RUNNING) return "";
    return Network::getInstance()->getIp();
}

Port ExtensionServer::getPort()
{
    if (this->state != STATE_RUNNING) return 0;
    return Network::getInstance()->getPort();
}

bool ExtensionServer::sendMessage(Extension* ext, std::string message)
{
    if (this->state != STATE_RUNNING)
    {
        this->lastError = "sendMessage: Server is not started";
        return false;
    }
    return Network::getInstance()->sendData(
        ext->getIp(), ext->getPort(),
        message
    );
}

bool ExtensionServer::sendMessage(Extension* ext, unsigned char* data, int length)
{
    if (this->state != STATE_RUNNING)
    {
        this->lastError = "sendMessage: Server is not started";
        return false;
    }
    return Network::getInstance()->sendData(
        ext->getIp(), ext->getPort(),
        data, length
    );
}

void ExtensionServer::update(float dt) {
    Network* net = Network::getInstance();
    net->update(dt);
    if (net->hasPaquets())
    {
        std::vector<NetworkPacket> packets = net->getPaquets();
        for (NetworkPacket packet : packets)
        {
            this->_process_packet(packet);
        }
    }
}