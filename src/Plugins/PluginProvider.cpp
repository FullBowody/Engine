#include <iostream>
#include <filesystem>
#include <fstream>
#include "json.hpp"
#include "Plugins/PluginProvider.hpp"

PluginProvider::PluginProvider()
{
}

PluginProvider::~PluginProvider()
{
}

void PluginProvider::retreivePlugins()
{
    for (const auto& entry : std::filesystem::directory_iterator(this->PLUGINS_FOLDER))
    {
        if (entry.is_directory())
        {
            std::string pluginFolder = entry.path().string();
            std::string pluginManifest = pluginFolder + "/plugin.json";

            // load plugin.json
            std::ifstream file(pluginManifest);
            nlohmann::json json;
            file >> json;
            
            // get values
            std::string name = json["name"];
            std::string description = json["description"];
            std::string author = json["author"];
            std::string version = json["version"];
            PluginType type = json["type"] == "camera" ? PluginType::CAMERA : PluginType::UNKNOWN;

            // create PluginDescriptor
            PluginDescriptor descriptor(name, description, author, version, type, pluginFolder);

            // add to plugins
            this->plugins.push_back(descriptor);
        }
    }
}

std::vector<PluginDescriptor> PluginProvider::getPlugins()
{
    return std::vector<PluginDescriptor>(this->plugins);
}

std::vector<PluginDescriptor> PluginProvider::getPlugins(PluginType type)
{
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
