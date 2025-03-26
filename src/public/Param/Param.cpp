#include <iostream>
#include "Params/Param.hpp"

#define CHECK_NO_ENTRY() { std::cerr << "Reached CHECK_NO_ENTRY at line " << __LINE__ << " in " << __FILE__ << std::endl; exit(1); }

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
bool Param::asBool() const { CHECK_NO_ENTRY(); }
int Param::asInt() const { CHECK_NO_ENTRY(); }
int Param::asEnum() const { CHECK_NO_ENTRY(); }
float Param::asFloat() const { CHECK_NO_ENTRY(); }
std::string Param::asString() const { CHECK_NO_ENTRY(); }

// if not overriden, should not be called
void Param::setValue(const bool& value) { CHECK_NO_ENTRY(); }
void Param::setValue(const int& value) { CHECK_NO_ENTRY(); }
void Param::setValue(const float& value) { CHECK_NO_ENTRY(); }
void Param::setValue(char* str) { setValue(std::string(str)); }
void Param::setValue(const std::string& value) { CHECK_NO_ENTRY(); }

// if not overriden, should not be called
void Param::onValue(std::function<void(const bool&)> listener) { CHECK_NO_ENTRY(); }
void Param::onValue(std::function<void(const int&)> listener) { CHECK_NO_ENTRY(); }
void Param::onValue(std::function<void(const float&)> listener) { CHECK_NO_ENTRY(); }
void Param::onValue(std::function<void(const std::string&)> listener) { CHECK_NO_ENTRY(); }
