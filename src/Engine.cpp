#include "Engine.hpp"
#include <iostream>

Engine::Engine()
{
    
}

Engine::~Engine()
{
    
}

int Engine::start()
{
    return 0;
}

int Engine::update(float dt)
{
    return 0;
}

int Engine::stop()
{
    return 0;
}


    // #include <torch/torch.h>
    // #include <torch/script.h>

    // std::string modelPath;
    // std::cout << "Enter model path: ";
    // std::cin >> modelPath;
    // std::cout << "Loading model from " << modelPath << "..." << std::endl;
    // torch::jit::script::Module module = torch::jit::load(modelPath);
    // std::cout << "Model loaded successfully!" << std::endl;

    // std::vector<torch::jit::IValue> inputs;
    // inputs.push_back(torch::ones({1, 192, 192, 3}));
    // at::Tensor output = module.forward(inputs).toTensor();

    // std::cout << "Output: " << output << std::endl;