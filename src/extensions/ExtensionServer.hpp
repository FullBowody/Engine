#pragma once
#include <string>
#include <vector>
#include "../common.hpp"
#include "../Callback.hpp"
#include "Extension.hpp"

class ExtensionServer
{
private:
    static ExtensionServer* instance;

    std::vector<Extension*> extensions;
    State state = STATE_STOPPED;
    std::string lastError = "";

    Callback* updateCallback = nullptr;

public:
    static ExtensionServer* getInstance();

    ExtensionServer();
    ~ExtensionServer();

    bool start();
    bool stop();
    State getState();
    std::string getLastError();

    std::vector<Extension*> getExtensions();
    Extension* getExtension(std::string name);
    void onExtensionUpdate(Callback* callback);

    bool addExtension(Extension* ext);
    bool removeExtension(std::string name, std::string key);
    void _onPaquet(void* data);
};