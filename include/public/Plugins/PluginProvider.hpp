#pragma once
#include <vector>
#include "utils.hpp"
#include "plugins/PluginDescriptor.hpp"

class DLLExport PluginProvider
{
private:
    static PluginProvider* instance;
    static const std::string PLUGINS_FOLDER;

    PluginProvider();
    std::vector<PluginDescriptor> plugins;

public:
    ~PluginProvider();

    static PluginProvider& getInstance()
    {
        if (!instance) instance = new PluginProvider();
        return *instance;
    }

    virtual void refreshPlugins();
    virtual PluginDescriptor getPlugin(std::string name);
    virtual std::vector<PluginDescriptor> getPlugins();
    virtual std::vector<PluginDescriptor> getPlugins(PluginType type);
};
