#pragma once
#include <string>
#include "../common/common.hpp"

const std::string DEFAULT_EXTENSION_NAME = "Unknown Extension";
const std::string DEFAULT_EXTENSION_IP = "xxx.xxx.xxx.xxx";
const Port DEFAULT_EXTENSION_PORT = 0;

class Extension
{
private:
    std::string name;
    std::string key;
    std::string ip;
    Port port;

public:
    Extension();
    Extension(std::string name, std::string key, std::string ip, Port port);

    std::string getName();
    std::string getKey();
    std::string getIp();
    Port getPort();

    std::string toJSON();
};