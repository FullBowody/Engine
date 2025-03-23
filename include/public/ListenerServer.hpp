#pragma once
#include "utils.hpp"

class ENGINE_API ListenerServer
{
public:
    enum ListenerServerState
    {
        STARTING,
        LISTENING,
        STOPPED
    };

protected:
    ListenerServerState state;
    void serverMain();

public:
    ListenerServer();

    virtual ListenerServerState getState() const;
};
