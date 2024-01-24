// Path: Engine.cpp
#include "Engine.hpp"
#include <iostream>

Engine::Engine()
{
    std::cout << "Engine::Engine()" << std::endl;
}

Engine::~Engine()
{
    std::cout << "Engine::~Engine()" << std::endl;
}

void Engine::Run()
{
    std::cout << "Engine::Run()" << std::endl;
}
