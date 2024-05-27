#pragma once
#include <iostream>
#include "Plugins/PluginLoader.hpp"

template <class T>
class DLLExport PluginHandle
{
private:
    PluginLoader<T>* loader = nullptr;
    T* plugin = nullptr;

public:
    PluginHandle(std::string path)
    {
        this->loader = new PluginLoader<T>(path);
    }

    ~PluginHandle()
    {
        if (this->loader)
        {
            if (this->plugin)
                this->loader->destroyPlugin(this->plugin);
            delete loader;
        }
    }

    T* getPlugin()
    {
        if (!this->plugin)
            this->plugin = this->loader->createPlugin();
        return this->plugin;
    }
};
