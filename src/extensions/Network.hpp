#pragma once
#include <string>
#include <thread>
#include "../common/common.hpp"
#include "../common/Promise.hpp"

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
#endif

const std::string IP_LOCALHOST = "127.0.0.1";

struct NetworkPacket {
    std::string data;
    std::string ip;
    Port port;
};

class Network
{
private:
    static Network* instance;

    std::string ip;
    Port port;
    State state;
    std::string lastError;
    std::thread thread;

    Promise* startPromise = nullptr;
    Promise* stopPromise = nullptr;
    ArgsCallback* dataCallback = nullptr;

#ifdef _WIN32
    SOCKET sock;
    sockaddr_in addr;
#endif

public:
    static Network* getInstance();

    ArgsCallback* _start_resolve = nullptr;
    ArgsCallback* _start_reject = nullptr;
    ArgsCallback* _stop_resolve = nullptr;
    ArgsCallback* _stop_reject = nullptr;
    bool isSetup = false;

    Network();
    ~Network();
    std::string getLastError();

    bool setup(Port port = DEFAULT_PORT, std::string ip = IP_LOCALHOST);
    Promise* start();
    Promise* stop();

    void onDataReceived(ArgsCallback* callback);
    bool sendData(std::string ip, Port port, std::string data);
    bool sendData(std::string ip, Port port, unsigned char* data, int length);

    std::string getIp();
    Port getPort();
    void _run();
};