#ifdef _WIN32
#include "Network.hpp"
#include <chrono>

std::string getIP(sockaddr_in* addr)
{
    char ip[INET_ADDRSTRLEN] = "";
    inet_ntop(AF_INET, &(addr->sin_addr), ip, INET_ADDRSTRLEN);
    return std::string(ip);
}

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
    if (isSetup) return true;

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

    isSetup = true;
    return true;
}

Promise* Network::start()
{
    if (state != STATE_STOPPED)
        return this->startPromise;

    if (this->startPromise != nullptr)
        delete this->startPromise;

    this->startPromise = new Promise([this](void* c){
        PromiseCallback* pc = (PromiseCallback*) c;
        this->_start_resolve = new VoidArgsCallback([pc](void* c){
            pc->resolve->call(c);
        });
        this->_start_reject = new VoidArgsCallback([pc](void* c){
            pc->reject->call(c);
        });
    });
    state = STATE_STARTING;

    memset((char*) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (ip == IP_LOCALHOST || ip == "")
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
        this->_start_reject->call(&lastError);
        return this->startPromise;
    }

    // if ip not specified, set the current ip to the ip variable
    if (ip == IP_LOCALHOST || ip == "")
    {
        char hostname[1024] = "";
        gethostname(hostname, 1024);
        hostent* host = gethostbyname(hostname);
        if (host == NULL)
        {
            lastError = "start: gethostbyname failed (" + std::to_string(WSAGetLastError()) + ")";
            state = STATE_ERROR;
            this->_start_reject->call(&lastError);
            return this->startPromise;
        }
        char buff[INET_ADDRSTRLEN] = "";
        inet_ntop(AF_INET, *host->h_addr_list, buff, INET_ADDRSTRLEN);
        this->ip = std::string(buff);
    }

    thread = std::thread(&Network::_run, this);
    return this->startPromise;
}

Promise* Network::stop()
{
    if (state != STATE_STARTED)
        return this->stopPromise;

    if (this->stopPromise != nullptr)
        delete this->stopPromise;

    this->stopPromise = new Promise([this](void* c){
        PromiseCallback* pc = (PromiseCallback*) c;
        this->_stop_resolve = new VoidArgsCallback([pc](void* c){
            pc->resolve->call(c);
        });
        this->_stop_reject = new VoidArgsCallback([pc](void* c){
            pc->reject->call(c);
        });
    });
    state = STATE_STOPPING;

    return this->stopPromise;
}

void Network::_run()
{
    sockaddr_in reqAddr;
    int reqAddrlen = sizeof(reqAddr);
    const int BUFFER_LENGTH = 1024;
    char buffer[BUFFER_LENGTH];
    state = STATE_STARTED;

    if (this->_start_resolve != nullptr)
        this->_start_resolve->call(nullptr);

    while (state == STATE_STARTED)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        memset(buffer, 0, BUFFER_LENGTH);
        if (recvfrom(sock, buffer, BUFFER_LENGTH, 0, (sockaddr*) &reqAddr, &reqAddrlen) == SOCKET_ERROR)
        {
            int error = WSAGetLastError();
            if (error != WSAEWOULDBLOCK)
            {
                lastError = "thread: recvfrom failed (" + std::to_string(error) + ")";
                state = STATE_ERROR;
                break;
            }
        }

        std::string data(buffer);
        if (data.length() > 15)
        {
            if (dataCallback != nullptr)
            {
                Port port = ntohs(reqAddr.sin_port);
                std::string ip = getIP(&reqAddr);
                NetworkPacket np{data, ip, port};
                dataCallback->call((void*)&np);
            }
        }
    }

    if (state != STATE_ERROR)
        state = STATE_STOPPED;

    if (this->_stop_resolve != nullptr)
        this->_stop_resolve->call(nullptr);
}

void Network::onDataReceived(ArgsCallback* callback)
{
    dataCallback = callback;
}

bool Network::sendData(std::string ip, Port port, std::string data)
{
    int length = data.length();
    unsigned char* buffer = new unsigned char[length];
    memcpy(buffer, data.c_str(), length);
    return sendData(ip, port, buffer, length);
}

bool Network::sendData(std::string ip, Port port, unsigned char* data, int length)
{
    if (state != STATE_STARTED)
    {
        lastError = "sendData: Network not started";
        return false;
    }

    sockaddr_in dest;
    memset((char*) &dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    inet_pton(dest.sin_family, ip.c_str(), &dest.sin_addr.S_un.S_addr);

    if (sendto(sock, (char*) data, length, 0, (sockaddr*) &dest, sizeof(dest)) == SOCKET_ERROR)
    {
        lastError = "sendData: sendto failed (" + std::to_string(WSAGetLastError()) + ")";
        state = STATE_ERROR;
        return false;
    }

    return true;
}

std::string Network::getIp()
{
    return ip;
}

Port Network::getPort()
{
    return port;
}

#endif