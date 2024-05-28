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
    ~PluginDescriptor();

    virtual std::string getName() const;
    virtual std::string getDescription() const;
    virtual std::string getAuthor() const;
    virtual std::string getVersion() const;
    virtual PluginType getType() const;

    template <typename T>
    PluginHandle<T>* createHandle() const
    {
        return new PluginHandle<T>(this->folder);
    }
};
