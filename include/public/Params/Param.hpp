#pragma once
#include <string>
#include "Event/EventManager.hpp"
#include "utils.hpp"

enum class ParamType
{
    BOOL,
    INT,
    FLOAT,
    STRING,
    ENUM
};

class ENGINE_API Param
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
    virtual void setValue(const bool& value);
    virtual void setValue(const int& value);
    virtual void setValue(const float& value);
    virtual void setValue(char* str);
    virtual void setValue(const std::string& value);

    // if not overriden, should not be called
    virtual void onValue(std::function<void(const bool&)> listener);
    virtual void onValue(std::function<void(const int&)> listener);
    virtual void onValue(std::function<void(const float&)> listener);
    virtual void onValue(std::function<void(const std::string&)> listener);
};
