#pragma once
#include <string>
#include <memory>
#include <ostream>
#include "utils.hpp"
#include "Plugins/PluginHandle.hpp"

enum class PluginType
{
    CAPTURE,
    UNKNOWN
};

class ENGINE_API PluginDescription
{
private:
    PluginType type;
    std::string name;
    std::string description;
    std::string author;
    std::string version;

    std::string folder;

public:
    PluginDescription(std::string name, std::string description, std::string author, std::string version, PluginType type, std::string folder)
        : name(name), description(description), author(author), version(version), type(type), folder(folder) {}
    PluginDescription(const PluginDescription& other)
        : name(other.name), description(other.description), author(other.author), version(other.version), type(other.type), folder(other.folder) {}
    virtual ~PluginDescription() {}

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

    friend std::ostream& operator<<(std::ostream& os, const PluginDescription& description)
    {
        os << "Plugin(name=" << description.name << ", version=" << description.version << ")";
        return os;
    }
};
