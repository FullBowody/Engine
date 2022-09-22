#include "../json/json11.hpp"
#include "ExtensionServer.hpp"
#include "Network.hpp"

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

Promise* ExtensionServer::start()
{
    if (this->state == STATE_STARTED || this->state == STATE_STARTING)
        return this->startPromise;

    if (this->startPromise != nullptr)
        delete this->startPromise;

    state = STATE_STARTING;
    this->startPromise = new Promise([](void* c){
        PromiseCallback* pc = (PromiseCallback*) c;
        ExtensionServer::getInstance()->_start_resolve = pc->resolve;
        ExtensionServer::getInstance()->_start_reject = pc->reject;
    });

    Network* net = Network::getInstance();
    if (!net->setup())
    {
        lastError = net->getLastError();
        state = STATE_ERROR;
        this->_start_reject->call(&lastError);
        return this->startPromise;
    }

    net->onDataReceived(new TypedArgsCallback<ExtensionServer>(this, &ExtensionServer::_onPaquet));
    Promise* p = net->start();
    if (p == nullptr)
    {
        state = STATE_ERROR;
        lastError = "start: Failed to start network";
        this->_start_reject->call(&lastError);
        return this->startPromise;
    }

    p->onResolve([this](void* c){
        this->state = STATE_STARTED;
        this->_start_resolve->call(nullptr);
    })->onReject([this](void* c){
        this->state = STATE_ERROR;
        this->lastError = "start: Failed to start network";
        this->_start_reject->call(&this->lastError);
    });
    return this->startPromise;
}

Promise* ExtensionServer::stop()
{
    if (this->state != STATE_STARTED)
        return this->stopPromise;

    if (this->stopPromise != nullptr)
        delete this->stopPromise;

    this->stopPromise = new Promise([](void* c){
        PromiseCallback* pc = (PromiseCallback*) c;
        ExtensionServer* e = ExtensionServer::getInstance();
        e->_stop_resolve = pc->resolve;
        e->_stop_reject = pc->reject;
    });
    state = STATE_STOPPING;

    Promise* p = Network::getInstance()->stop();
    if (p == nullptr)
    {
        this->state = STATE_ERROR;
        this->lastError = "stop: Failed to stop network";
        this->_stop_reject->call(&this->lastError);
        return this->stopPromise;
    }

    p->onResolve([this](void*c){
        this->state = STATE_STOPPED;
        this->_stop_resolve->call(nullptr);
    })->onReject([this](void* c){
        this->state = STATE_ERROR;
        this->lastError = "stop: Failed to stop network";
        this->_stop_reject->call(&this->lastError);
    });
    return this->stopPromise;
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

void ExtensionServer::_set_state(State state)
{
    this->state = state;
}

std::string ExtensionServer::getIp()
{
    if (state != STATE_STARTED)
        return "";
    return Network::getInstance()->getIp();
}

Port ExtensionServer::getPort()
{
    if (state != STATE_STARTED)
        return 0;
    return Network::getInstance()->getPort();
}

bool ExtensionServer::sendMessage(Extension* ext, std::string message)
{
    if (state != STATE_STARTED)
    {
        lastError = "sendMessage: Server is not started";
        return false;
    }
    return Network::getInstance()->sendData(ext->getIp(), ext->getPort(), message);
}

bool ExtensionServer::sendMessage(Extension* ext, unsigned char* data, int length)
{
    if (state != STATE_STARTED)
    {
        lastError = "sendMessage: Server is not started";
        return false;
    }
    return Network::getInstance()->sendData(ext->getIp(), ext->getPort(), data, length);
}