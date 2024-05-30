#include "Param/Param.hpp"

#define checkNoEntry exit(1);

Param::Param(std::string name, ParamType type)
    : name(name), type(type) {}

Param::~Param() {}

std::string Param::getName() const
{
    return name;
}

ParamType Param::getType() const
{
    return type;
}

// if not overriden, should not be called
bool Param::asBool() const { checkNoEntry }
int Param::asInt() const { checkNoEntry }
int Param::asEnum() const { checkNoEntry }
float Param::asFloat() const { checkNoEntry }
std::string Param::asString() const { checkNoEntry }

// if not overriden, should not be called
void Param::setValue(bool value) { checkNoEntry }
void Param::setValue(int value) { checkNoEntry }
void Param::setValue(float value) { checkNoEntry }
void Param::setValue(std::string value) { checkNoEntry }

// if not overriden, should not be called
void Param::onValue(Callback<bool>* listener) { checkNoEntry }
void Param::onValue(Callback<int>* listener) { checkNoEntry }
void Param::onValue(Callback<float>* listener) { checkNoEntry }
void Param::onValue(Callback<std::string>* listener) { checkNoEntry }
