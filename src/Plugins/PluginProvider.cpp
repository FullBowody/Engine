#include <iostream>
#include <filesystem>
#include <fstream>
#include "json.hpp"
#include "Plugins/PluginProvider.hpp"

const std::string PluginProvider::PLUGINS_FOLDER = "plugins";

PluginProvider::PluginProvider()
{
}

PluginProvider::~PluginProvider()
{
}

void PluginProvider::refreshPlugins()
{
    this->plugins.clear();

    if (!std::filesystem::exists(this->PLUGINS_FOLDER))
        std::filesystem::create_directory(this->PLUGINS_FOLDER);

    for (const auto& entry : std::filesystem::directory_iterator(this->PLUGINS_FOLDER))
    {
        if (entry.is_directory())
        {
            std::string pluginFolder = entry.path().string();
            std::string pluginManifest = pluginFolder + "/plugin.json";

            std::ifstream file(pluginManifest);
            nlohmann::json json;
            file >> json;
            
            // TODO : add json validation
            std::string name = json["name"];
            std::string description = json["description"];
            std::string author = json["author"];
            std::string version = json["version"];
            PluginType type = json["type"] == "Camera" ? PluginType::CAMERA : PluginType::UNKNOWN;

            PluginDescriptor descriptor(name, description, author, version, type, pluginFolder);
            this->plugins.push_back(descriptor);
        }
    }
}

PluginDescriptor PluginProvider::getPlugin(std::string name)
{
    if (this->plugins.empty()) this->refreshPlugins();

    for (auto plugin : this->plugins)
    {
        if (plugin.getName() == name)
        {
            return plugin;
        }
    }
    return PluginDescriptor("", "", "", "", PluginType::UNKNOWN, "");
}

std::vector<PluginDescriptor> PluginProvider::getPlugins()
{
    if (this->plugins.empty()) this->refreshPlugins();
    return this->plugins;
}

std::vector<PluginDescriptor> PluginProvider::getPlugins(PluginType type)
{
    if (this->plugins.empty()) this->refreshPlugins();

    std::vector<PluginDescriptor> filtered;
    for (auto plugin : this->plugins)
    {
        if (plugin.getType() == type)
        {
            filtered.push_back(plugin);
        }
    }
    return filtered;
}
