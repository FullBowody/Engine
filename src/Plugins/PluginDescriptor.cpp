#include "Plugins/PluginDescriptor.hpp"

PluginDescriptor::PluginDescriptor(std::string name, std::string description, std::string author,
                                   std::string version, PluginType type, std::string folder)
    : name(name), description(description), author(author), version(version), folder(folder), type(type)
{
}

PluginDescriptor::~PluginDescriptor()
{
}


std::string PluginDescriptor::getName()
{
    return this->name;
}

std::string PluginDescriptor::getDescription()
{
    return this->description;
}

std::string PluginDescriptor::getAuthor()
{
    return this->author;
}

std::string PluginDescriptor::getVersion()
{
    return this->version;
}


PluginType PluginDescriptor::getType()
{
    return this->type;
}
