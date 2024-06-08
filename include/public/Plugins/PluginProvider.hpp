#pragma once
#include <vector>
#include "utils.hpp"
#include "plugins/PluginDescriptor.hpp"

class DLLExport PluginProvider
{
private:
    static const std::string PLUGINS_FOLDER;
    
    std::vector<PluginDescriptor> plugins;

public:
    PluginProvider();
    ~PluginProvider();

    virtual void refreshPlugins();
    virtual PluginDescriptor getPlugin(std::string name);
    virtual std::vector<PluginDescriptor> getPlugins();
    virtual std::vector<PluginDescriptor> getPlugins(PluginType type);
};
