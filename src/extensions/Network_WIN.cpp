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
    Network::instance = this;
}

Network::~Network()
{
    this->stop();
    closesocket(this->sock);
    WSACleanup();
}

bool Network::setup(Port port, std::string ip)
{
    if (this->state == STATE_ERROR) return false;
    if (this->state == STATE_RUNNING) return true;

    this->port = port;
    this->ip = ip;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        this->lastError = "setup: WSAStartup failed (" + std::to_string(WSAGetLastError()) + ")";
        this->state = STATE_ERROR;
        return false;
    }
    
    this->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->sock == INVALID_SOCKET)
    {
        this->lastError = "setup: socket failed (" + std::to_string(WSAGetLastError()) + ")";
        this->state = STATE_ERROR;
        return false;
    }

    u_long iMode = 1; // 1 = non-blocking, 0 = blocking
    if (ioctlsocket(sock, FIONBIO, &iMode) != 0)
    {
        this->lastError = "setup: ioctlsocket failed (" + std::to_string(WSAGetLastError()) + ")";
        this->state = STATE_ERROR;
        return false;
    }

    return true;
}

bool Network::start()
{
    if (this->state == STATE_ERROR) return false;
    if (this->state == STATE_RUNNING) return true;

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
        return false;
    }

    // if ip not specified, set the current ip to the ip variable
    if (ip == IP_LOCALHOST || ip == "")
    {
        char hostname[1024] = "";
        gethostname(hostname, 1024);
        hostent* host = gethostbyname(hostname);
        // TODO : change from gesthostbyname to getaddrinfo
        if (host == NULL)
        {
            lastError = "start: gethostbyname failed (" + std::to_string(WSAGetLastError()) + ")";
            state = STATE_ERROR;
            return false;
        }
        char buff[INET_ADDRSTRLEN] = "";
        inet_ntop(AF_INET, *host->h_addr_list, buff, INET_ADDRSTRLEN);
        this->ip = std::string(buff);
    }
    
    this->state = STATE_RUNNING;

    return true;
}

bool Network::stop()
{
    if (this->state == STATE_ERROR) return false;
    if (this->state == STATE_STOPPED) return true;

    this->state = STATE_STOPPED;

    return true;
}

bool Network::_check_for_paquet()
{
    if (this->state == STATE_ERROR) return false;
    if (this->state == STATE_STOPPED) return true;
    
    sockaddr_in reqAddr;
    int reqAddrlen = sizeof(reqAddr);
    const int BUFFER_LENGTH = 1024;
    char buffer[BUFFER_LENGTH];

    if (recvfrom(sock, buffer, BUFFER_LENGTH, 0, (sockaddr*) &reqAddr, &reqAddrlen) == SOCKET_ERROR)
    {
        int error = WSAGetLastError();
        if (error != WSAEWOULDBLOCK)
        {
            this->lastError = "Recvfrom failed (" + std::to_string(error) + ")";
            this->state = STATE_ERROR;
            return false;
        }
    }

    std::string data(buffer);
    if (data.length() < 10)
        return false;
        
    Port port = ntohs(reqAddr.sin_port);
    std::string ip = getIP(&reqAddr);
    this->paquets.push_back(NetworkPacket{data, ip, port});

    return true;
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
    if (this->state != STATE_RUNNING)
    {
        this->lastError = "sendData: Network not started";
        return false;
    }

    sockaddr_in dest;
    memset((char*) &dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    inet_pton(dest.sin_family, ip.c_str(), &dest.sin_addr.S_un.S_addr);

    if (sendto(sock, (char*) data, length, 0, (sockaddr*) &dest, sizeof(dest)) == SOCKET_ERROR)
    {
        this->lastError = "sendData: sendto failed (" + std::to_string(WSAGetLastError()) + ")";
        this->state = STATE_ERROR;
        return false;
    }

    return true;
}

void Network::update(float dt) {
    paquet_timelapse += dt;
    if (paquet_timelapse > NETWORK_UPDATE_LAPSE)
    {
        paquet_timelapse = 0.f;
        _check_for_paquet();
    }
}

std::string Network::getIp()
{
    return this->ip;
}

Port Network::getPort()
{
    return this->port;
}

std::string Network::getLastError()
{
    std::string err = this->lastError;
    this->lastError = "";
    return err;
}

bool Network::hasPaquets()
{
    return this->paquets.size() > 0;
}

NetworkPacket Network::getPaquet()
{
    NetworkPacket p = this->paquets[0];
    this->paquets.erase(this->paquets.begin());
    return p;
}

std::vector<NetworkPacket> Network::getPaquets()
{
    std::vector<NetworkPacket> p = this->paquets;
    this->paquets.clear();
    return p;
}

#endif