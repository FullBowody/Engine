#pragma once
#include "Param/Param.hpp"

class ParamString: public Param
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

    void setValue(std::string value) override
    {
        this->value = value;
        onValueEvent.dispatchEvent(value);
    }

    void onValue(Callback<std::string>* listener) override
    {
        onValueEvent.attachListener(listener);
    }
};
