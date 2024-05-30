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
    Param(std::string name, ParamType type);
    virtual ~Param();

    virtual std::string getName() const;
    virtual ParamType getType() const;

    // if not overriden, should not be called
    virtual bool asBool() const;
    virtual int asInt() const;
    virtual int asEnum() const;
    virtual float asFloat() const;
    virtual std::string asString() const;

    // if not overriden, should not be called
    virtual void setValue(bool value);
    virtual void setValue(int value);
    virtual void setValue(float value);
    virtual void setValue(std::string value);

    // if not overriden, should not be called
    virtual void onValue(Callback<bool>* listener);
    virtual void onValue(Callback<int>* listener);
    virtual void onValue(Callback<float>* listener);
    virtual void onValue(Callback<std::string>* listener);
};
