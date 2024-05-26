#pragma once
#include "Param/Param.hpp"

class ParamInt: public Param
{
private:
    int value;
    EventManager<int> onValueEvent;

public:
    ParamInt(std::string name)
        : Param(name, ParamType::INT) {}

    ~ParamInt() {}

    int asInt() const override
    {
        return value;
    }

    void setValue(int value) override
    {
        this->value = value;
        onValueEvent.dispatchEvent(value);
    }

    void onValue(Callback<int>* listener) override
    {
        onValueEvent.attachListener(listener);
    }
};
