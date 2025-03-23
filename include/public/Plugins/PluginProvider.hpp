#pragma once
#include <vector>
#include "utils.hpp"
#include "Plugins/PluginDescription.hpp"

class ENGINE_API PluginProvider
{
private:
    std::string pluginsFolder;
    std::vector<PluginDescription> plugins;

public:
    PluginProvider();
    ~PluginProvider();

    virtual void setPluginsFolder(std::string folder);
    virtual void refreshPlugins();
    virtual std::optional<PluginDescription> getPlugin(std::string name);
    virtual const std::vector<PluginDescription>& getPlugins();
    virtual std::vector<PluginDescription> getPlugins(PluginType type);
};
