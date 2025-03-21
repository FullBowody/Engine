#include "Params/Param.hpp"

#define CHECK_NO_ENTRY() exit(1)

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
void Param::setValue(bool value) { CHECK_NO_ENTRY(); }
void Param::setValue(int value) { CHECK_NO_ENTRY(); }
void Param::setValue(float value) { CHECK_NO_ENTRY(); }
void Param::setValue(std::string value) { CHECK_NO_ENTRY(); }

// if not overriden, should not be called
void Param::onValue(Callback<bool>* listener) { CHECK_NO_ENTRY(); }
void Param::onValue(Callback<int>* listener) { CHECK_NO_ENTRY(); }
void Param::onValue(Callback<float>* listener) { CHECK_NO_ENTRY(); }
void Param::onValue(Callback<std::string>* listener) { CHECK_NO_ENTRY(); }
