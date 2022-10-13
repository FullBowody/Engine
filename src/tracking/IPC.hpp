#pragma once
#include <vector>

class IPC
{
private:

public:
    IPC();
    ~IPC();

    bool createChild();
    bool deleteChild();
    bool send(std::vector<unsigned char> buff);
    bool isDataAvailable();
    std::vector<unsigned char> getData();

    void update(float dt);
};