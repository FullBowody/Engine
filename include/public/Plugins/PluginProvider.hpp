#pragma once
#include <vector>
#include "utils.hpp"
#include "plugins/PluginDescriptor.hpp"

class DLLExport PluginProvider
{
private:
    std::string pluginsFolder;
    std::vector<PluginDescriptor> plugins;

public:
    PluginProvider();
    ~PluginProvider();

    virtual void setPluginsFolder(std::string folder);
    virtual void refreshPlugins();
    virtual PluginDescriptor getPlugin(std::string name);
    virtual std::vector<PluginDescriptor> getPlugins();
    virtual std::vector<PluginDescriptor> getPlugins(PluginType type);
};
