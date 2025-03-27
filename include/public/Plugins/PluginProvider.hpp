#pragma once
#include <vector>
#include "utils.hpp"
#include "Plugins/PluginDescription.hpp"

class ENGINE_API PluginProvider
{
private:
    std::string pluginsFolder;
    std::vector<std::shared_ptr<PluginDescription>> plugins;

public:
    PluginProvider();
    ~PluginProvider();

    virtual void setPluginsFolder(std::string folder);
    virtual void refreshPlugins();
    virtual std::shared_ptr<PluginDescription> getPlugin(std::string name);
    virtual const std::vector<std::shared_ptr<PluginDescription>>& getPlugins();
    virtual std::vector<std::shared_ptr<PluginDescription>> getPlugins(PluginType type);
};
