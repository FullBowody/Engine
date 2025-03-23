#include "ListenerServer.hpp"
#include <iostream>
#include <thread>

#include "App.h"

ListenerServer::ListenerServer()
{
    std::thread serverThread(&ListenerServer::serverMain, this);
    serverThread.detach();
}

void ListenerServer::serverMain()
{
    std::cout << "Starting server" << std::endl;
    this->state = ListenerServer::STARTING;

    struct UserData {};
    uWS::App().ws<UserData>("/", {
        .open = [](auto *ws) {
            std::cout << "Client connected" << std::endl;
        },
        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
            std::cout << "Received message: " << message << std::endl;
            ws->send(message, opCode);
        },
        .close = [](auto *ws, int code, std::string_view message) {
            std::cout << "Client disconnected" << std::endl;
        }
    }).listen(5621, [this](auto *token) {
        if (token)
        {
            std::cout << "Listening on port " << 5621 << std::endl;
            this->state = ListenerServer::LISTENING;
        }
        else
        {
            std::cout << "Failed to listen on port " << 5621 << std::endl;
            this->state = ListenerServer::STOPPED;
        }
    }).run();
}

ListenerServer::ListenerServerState ListenerServer::getState() const
{
    return this->state;
}
