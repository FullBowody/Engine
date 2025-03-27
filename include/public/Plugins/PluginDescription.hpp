#pragma once
#include <string>
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
    PluginDescription();
    PluginDescription(std::string name, std::string description, std::string author, std::string version, PluginType type, std::string folder);
    virtual ~PluginDescription();

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

    friend std::ostream& operator<<(std::ostream& os, const PluginDescription& description)
    {
        os << "Plugin(name=" << description.name << ", version=" << description.version << ")";
        return os;
    }
};
