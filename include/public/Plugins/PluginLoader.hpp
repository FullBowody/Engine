#pragma once
#include <iostream>
#include "utils.hpp"
#include "DLLLoader.hpp"

#ifdef _WIN32
const std::string PLUGIN_LIB = "./plugin.dll";
#else
const std::string PLUGIN_LIB = "./plugin.so";
#endif

template <class T>
class DLLExport PluginLoader
{
private:
    DLLLoader* loader = nullptr;
    T* (*pluginCreator)() = nullptr;
    void (*pluginDestroyer)(T*) = nullptr;

    void loadDLL(std::string path)
    {
        if (this->loader) delete loader;
        this->loader = new DLLLoader(path);
        this->pluginCreator = (T*(*)()) loader->resolve("createPlugin");
        this->pluginDestroyer = (void (*)(T*)) loader->resolve("destroyPlugin");
    }

public:
    PluginLoader()
    {
        loadDLL(PLUGIN_LIB);
    }

    PluginLoader(std::string path)
    {
        loadDLL(path + "/" + PLUGIN_LIB);
    }

    ~PluginLoader()
    {
        if (this->loader) delete loader;
    }

    T* createPlugin()
    {
        if (!this->pluginCreator)
        {
            std::cerr << std::endl << "Error: PluginLoader::pluginCreator not resolved!" << std::endl;
            return nullptr;
        }

        T* plugin = this->pluginCreator();
        return plugin;
    }

    void destroyPlugin(T* plugin)
    {
        if (!this->pluginDestroyer)
        {
            std::cerr << std::endl << "Error: PluginLoader::pluginDestroyer not resolved!" << std::endl;
            return;
        }

        std::cout << "this->pluginDestroyer(plugin);" << std::endl;
        this->pluginDestroyer(plugin);
        std::cout << "this->pluginDestroyer(plugin); [DONE]" << std::endl;
    }
};