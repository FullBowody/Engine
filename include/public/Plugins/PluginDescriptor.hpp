#pragma once
#include <string>
#include "utils.hpp"
#include "Plugins/PluginHandle.hpp"

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
    virtual ~PluginDescriptor();

    virtual std::string getName();
    virtual std::string getDescription();
    virtual std::string getAuthor();
    virtual std::string getVersion();
    virtual PluginType getType();

    template <typename T>
    PluginHandle<T>* createHandle()
    {
        return new PluginHandle<T>(this->folder);
    }
};
