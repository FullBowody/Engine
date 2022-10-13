#pragma once
#include <string>
#include <vector>
#include "../common/common.hpp"

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

    std::string ip = IP_LOCALHOST;
    Port port = 0;
    State state = STATE_STOPPED;
    std::string lastError = "";
    std::vector<NetworkPacket> paquets;

    float paquet_timelapse = 0.f;

#ifdef _WIN32
    SOCKET sock;
    sockaddr_in addr;
#endif

    bool _check_for_paquet();

public:
    static Network* getInstance();

    Network();
    ~Network();

    bool setup(Port port = DEFAULT_PORT, std::string ip = IP_LOCALHOST);
    bool start();
    bool stop();
    void update(float dt);

    bool sendData(std::string ip, Port port, std::string data);
    bool sendData(std::string ip, Port port, unsigned char* data, int length);
    bool hasPaquets();
    NetworkPacket getPaquet();
    std::vector<NetworkPacket> getPaquets();

    Port getPort();
    std::string getIp();
    std::string getLastError();
};