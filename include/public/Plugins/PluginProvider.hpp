#pragma once
#include <vector>
#include "utils.hpp"
#include "plugins/PluginDescriptor.hpp"

class DLLExport PluginProvider
{
private:
    const std::string PLUGINS_FOLDER = "plugins";

    std::vector<PluginDescriptor> plugins;

public:
    PluginProvider();
    ~PluginProvider();

    void retreivePlugins();
    std::vector<PluginDescriptor> getPlugins();
    std::vector<PluginDescriptor> getPlugins(PluginType type);
};