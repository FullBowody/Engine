#include "Extension.hpp"
#include "../json/json11.hpp"

Extension::Extension()
{
    this->name = DEFAULT_EXTENSION_NAME;
    this->key = "";
    this->port = DEFAULT_EXTENSION_PORT;
    this->ip = DEFAULT_EXTENSION_IP;
}

Extension::Extension(std::string name, std::string key, std::string ip, Port port)
{
    this->name = name;
    this->port = port;
    this->key = key;
    this->ip = ip;
}

std::string Extension::toJSON()
{
    json11::Json json = json11::Json::object {
        { "ip", getIp() },
        { "port", getPort() },
        { "name", getName() }
    };
    return json.dump();
}