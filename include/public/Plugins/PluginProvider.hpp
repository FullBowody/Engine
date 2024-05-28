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

    static PluginProvider& getInstance();

    void refreshPlugins();
    PluginDescriptor getPlugin(std::string name);
    std::vector<PluginDescriptor> getPlugins();
    std::vector<PluginDescriptor> getPlugins(PluginType type);
};