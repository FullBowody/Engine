#pragma once
#include <string>
#include <thread>
#include "../common.hpp"

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

    VoidCallback* startCallback = nullptr;
    VoidCallback* stopCallback = nullptr;
    ArgsCallback* dataCallback = nullptr;

#ifdef _WIN32
    SOCKET sock;
    sockaddr_in addr;
#endif

public:
    static Network* getInstance();

    Network();
    ~Network();
    std::string getLastError();

    bool setup(Port port = DEFAULT_PORT, std::string ip = IP_LOCALHOST);
    bool start(VoidCallback* callback = nullptr);
    bool stop(VoidCallback* callback = nullptr);

    void onDataReceived(ArgsCallback* callback);
    bool sendData(std::string data);
    bool sendData(unsigned char* data, int length);

    void _run();
};