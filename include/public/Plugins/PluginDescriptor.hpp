#pragma once
#include <string>
#include <ostream>
#include "utils.hpp"
#include "Plugins/PluginHandle.hpp"

enum class PluginType
{
    CAMERA,
    UNKNOWN
};

class PluginDescriptor
{
private:
    std::string name;
    std::string description;
    std::string author;
    std::string version;
    PluginType type;

    std::string folder;

public:
    PluginDescriptor(std::string name, std::string description, std::string author, std::string version, PluginType type, std::string folder)
        : name(name), description(description), author(author), version(version), type(type), folder(folder) {}
    PluginDescriptor(const PluginDescriptor& other)
        : name(other.name), description(other.description), author(other.author), version(other.version), type(other.type), folder(other.folder) {}
    ~PluginDescriptor() {}

    virtual std::string getName() const
    {
        return this->name;
    }
    virtual std::string getDescription() const
    {
        return this->description;
    }
    virtual std::string getAuthor() const
    {
        return this->author;
    }
    virtual std::string getVersion() const
    {
        return this->version;
    }
    virtual PluginType getType() const
    {
        return this->type;
    }

    template <typename T>
    PluginHandle<T>* createHandle() const
    {
        return new PluginHandle<T>(this->folder);
    }

    friend std::ostream& operator<<(std::ostream& os, const PluginDescriptor& descriptor)
    {
        // type=" << descriptor.type << ", 
        os << "Plugin(name=" << descriptor.name << ", version=" << descriptor.version << ")";
        return os;
    }
};
