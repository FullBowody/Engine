#pragma once
#include <string>
#include "utils.hpp"
#include "Plugins/PluginLoader.hpp"

enum class PluginType
{
    CAMERA,
    UNKNOWN
};

class DLLExport PluginDescriptor
{
private:
    std::string name;
    std::string description;
    std::string author;
    std::string version;
    PluginType type;
    
    std::string folder;

public:
    PluginDescriptor(std::string name, std::string description, std::string author,
                     std::string version, PluginType type, std::string folder);
    ~PluginDescriptor();

    std::string getName();
    std::string getDescription();
    std::string getAuthor();
    std::string getVersion();
    PluginType getType();

    template <typename T>
    T* createPlugin()
    {
        PluginLoader<T> loader(this->folder);
        return loader.createPlugin();
    }

    template <typename T>
    void destroyPlugin(T* plugin)
    {
        PluginLoader<T> loader(this->folder);
        loader.destroyPlugin(plugin);
    }
};
