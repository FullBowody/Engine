#ifdef _WIN32
#include "Network.hpp"
#include <iostream>

Network* Network::instance = nullptr;

Network* Network::getInstance()
{
    if (Network::instance == nullptr)
    {
        new Network();
    }
    return Network::instance;
}

Network::Network()
{
    if (Network::instance != nullptr)
    {
        delete Network::instance;
    }
    state = STATE_STOPPED;
    Network::instance = this;
}

Network::~Network()
{
    this->stop();
    closesocket(sock);
    WSACleanup();
}

std::string Network::getLastError()
{
    return lastError;
}

bool Network::setup(Port port, std::string ip)
{
    this->port = port;
    this->ip = ip;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        lastError = "setup: WSAStartup failed (" + std::to_string(WSAGetLastError()) + ")";
        state = STATE_ERROR;
        return false;
    }
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET)
    {
        lastError = "setup: socket failed (" + std::to_string(WSAGetLastError()) + ")";
        state = STATE_ERROR;
        return false;
    }

    u_long iMode = 1; // 1 = non-blocking, 0 = blocking
    if (ioctlsocket(sock, FIONBIO, &iMode) != 0)
    {
        lastError = "setup: ioctlsocket failed (" + std::to_string(WSAGetLastError()) + ")";
        state = STATE_ERROR;
        return false;
    }
    return true;
}

bool Network::start(VoidCallback* callback)
{
    if (state == STATE_STARTED) return true;
    if (state == STATE_STARTING) return true;
    if (state == STATE_ERROR) return false;

    startCallback = callback;
    state = STATE_STARTING;

    memset((char*) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (ip == IP_LOCALHOST)
    {
        addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    } else
    {
        inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr.S_un.S_addr);
    }

    if (bind(sock, (sockaddr*) &addr, sizeof(addr)) == SOCKET_ERROR)
    {
        lastError = "start: bind failed (" + std::to_string(WSAGetLastError()) + ")";
        state = STATE_ERROR;
        return false;
    }

    thread = std::thread(&Network::_run, this);

    return true;
}

bool Network::stop(VoidCallback* callback)
{
    if (state == STATE_STOPPED) return true;
    if (state == STATE_STOPPING) return true;
    if (state == STATE_ERROR) return false;

    stopCallback = callback;
    state = STATE_STOPPING;

    return true;
}

void Network::_run()
{
    sockaddr_in reqAddr;
    int reqAddrlen = sizeof(reqAddr);
    const int BUFFER_LENGTH = 1024;
    char buffer[BUFFER_LENGTH];
    state = STATE_STARTED;

    if (startCallback != nullptr)
    {
        startCallback->call();
    }

    while (state == STATE_STARTED)
    {
        memset(buffer, 0, BUFFER_LENGTH);
        if (recvfrom(sock, buffer, BUFFER_LENGTH, 0, (sockaddr*) &addr, &reqAddrlen) == SOCKET_ERROR)
        {
            int error = WSAGetLastError();
            if (error != WSAEWOULDBLOCK)
            {
                lastError = "thread: recvfrom failed (" + std::to_string(error) + ")";
                state = STATE_ERROR;
                std::cout << lastError << std::endl;
                break;
            }
        }

        std::string data(buffer);
        if (data.length() > 15)
        {
            if (dataCallback != nullptr)
            {
                char buff[INET_ADDRSTRLEN] = "";
                inet_ntop(AF_INET, &reqAddr.sin_addr, buff, INET_ADDRSTRLEN);
                // TODO : Find why IP address is not correct 
                Port port = ntohs(reqAddr.sin_port);
                NetworkPacket np{data, std::string(buff), port};
                dataCallback->call((void*)&np);
            }
        }
    }

    if (state != STATE_ERROR)
        state = STATE_STOPPED;

    if (stopCallback != nullptr)
    {
        stopCallback->call();
    }
}

void Network::onDataReceived(ArgsCallback* callback)
{
    dataCallback = callback;
}

bool Network::sendData(std::string data)
{
    int length = data.length();
    unsigned char* buffer = new unsigned char[length];
    memcpy(buffer, data.c_str(), length);
    return sendData(buffer, length);
}

bool Network::sendData(unsigned char* data, int length)
{
    if (state != STATE_STARTED)
    {
        lastError = "sendData: Network not started";
        return false;
    }

    if (sendto(sock, (char*) data, length, 0, (sockaddr*) &addr, sizeof(addr)) == SOCKET_ERROR)
    {
        lastError = "sendData: sendto failed (" + std::to_string(WSAGetLastError()) + ")";
        state = STATE_ERROR;
        return false;
    }

    return true;
}

#endif