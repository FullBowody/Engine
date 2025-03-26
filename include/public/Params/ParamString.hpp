#pragma once
#include "Params/Param.hpp"

class ENGINE_API ParamString: public Param
{
private:
    std::string value;
    EventManager<std::string> onValueEvent;

public:
    ParamString(std::string name)
        : Param(name, ParamType::STRING) {}

    ~ParamString() {}

    std::string asString() const override
    {
        return value;
    }

    void setValue(const std::string& value) override
    {
        this->value = value;
        onValueEvent.dispatchEvent(value);
    }

    void onValue(std::function<void(const std::string&)> listener) override
    {
        onValueEvent.addEventListener(listener);
    }
};
