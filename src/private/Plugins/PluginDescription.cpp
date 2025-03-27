#pragma once
#include <string>
#include "Plugins/PluginDescription.hpp"

PluginDescription::PluginDescription()
{
}

PluginDescription::PluginDescription(std::string name, std::string description, std::string author, std::string version, PluginType type, std::string folder)
    : name(name), description(description), author(author), version(version), type(type), folder(folder)
{
}

PluginDescription::~PluginDescription()
{
}

std::string PluginDescription::getName() const
{
    return this->name;
}

std::string PluginDescription::getDescription() const
{
    return this->description;
}

std::string PluginDescription::getAuthor() const
{
    return this->author;
}

std::string PluginDescription::getVersion() const
{
    return this->version;
}

PluginType PluginDescription::getType() const
{
    return this->type;
}
