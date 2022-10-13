#pragma once
#include <string>
#include <vector>
#include "../common/common.hpp"
#include "./Extension.hpp"
#include "Network.hpp"

class ExtensionServer
{
private:
    static ExtensionServer* instance;

    std::vector<Extension*> extensions;
    State state = STATE_STOPPED;
    std::string lastError = "";
    
    bool _process_packet(NetworkPacket packet);

public:
    static ExtensionServer* getInstance();

    ExtensionServer();
    ~ExtensionServer();

    bool start();
    bool stop();
    State getState();
    std::string getIp();
    Port getPort();
    std::string getLastError();

    std::vector<Extension*> getExtensions();
    Extension* getExtension(std::string name);
    void update(float dt);

    bool addExtension(Extension* ext);
    bool removeExtension(std::string name, std::string key);
    bool sendMessage(Extension* ext, std::string message);
    bool sendMessage(Extension* ext, unsigned char* message, int length);
};