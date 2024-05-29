#pragma once
#include <string>
#include "Event/EventManager.hpp"

enum class ParamType
{
    BOOL,
    INT,
    FLOAT,
    STRING,
    ENUM
};

class DLLExport Param
{
private:
    std::string name;
    ParamType type;

public:
    Param(std::string name, ParamType type)
        : name(name), type(type) {}

    virtual ~Param() {}

    virtual std::string getName() const
    {
        return name;
    }

    virtual ParamType getType() const
    {
        return type;
    }

    // if not overriden, should not be called
    virtual bool asBool() const { exit(1); }
    virtual int asInt() const { exit(1); }
    virtual int asEnum() const { exit(1); }
    virtual float asFloat() const { exit(1); }
    virtual std::string asString() const { exit(1); }

    // if not overriden, should not be called
    virtual void setValue(bool value) { exit(1); }
    virtual void setValue(int value) { exit(1); }
    virtual void setValue(float value) { exit(1); }
    virtual void setValue(std::string value) { exit(1); }

    // if not overriden, should not be called
    virtual void onValue(Callback<bool>* listener) { exit(1); }
    virtual void onValue(Callback<int>* listener) { exit(1); }
    virtual void onValue(Callback<float>* listener) { exit(1); }
    virtual void onValue(Callback<std::string>* listener) { exit(1); }
};
