#pragma once
#include <string>
#include <vector>
#include "../common/common.hpp"
#include "../common/Promise.hpp"
#include "./Extension.hpp"

class ExtensionServer
{
private:
    static ExtensionServer* instance;

    std::vector<Extension*> extensions;
    State state = STATE_STOPPED;
    std::string lastError = "";

    Callback* updateCallback = nullptr;

    Promise* stopPromise = nullptr;
    ArgsCallback* _start_resolve = nullptr;
    ArgsCallback* _start_reject = nullptr;

    Promise* startPromise = nullptr;
    ArgsCallback* _stop_resolve = nullptr;
    ArgsCallback* _stop_reject = nullptr;

public:
    static ExtensionServer* getInstance();

    ExtensionServer();
    ~ExtensionServer();

    Promise* start();
    Promise* stop();
    State getState();
    std::string getIp();
    Port getPort();
    std::string getLastError();

    std::vector<Extension*> getExtensions();
    Extension* getExtension(std::string name);
    void onExtensionUpdate(Callback* callback);

    bool addExtension(Extension* ext);
    bool removeExtension(std::string name, std::string key);
    bool sendMessage(Extension* ext, std::string message);
    bool sendMessage(Extension* ext, unsigned char* message, int length);
    
    void _onPaquet(void* data);
    void _set_state(State state);
};