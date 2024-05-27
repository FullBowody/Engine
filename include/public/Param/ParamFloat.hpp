#pragma once
#include "Param/Param.hpp"

class DLLExport ParamFloat: public Param
{
private:
    int value;
    EventManager<float> onValueEvent;

public:
    ParamFloat(std::string name)
        : Param(name, ParamType::FLOAT) {}

    ~ParamFloat() {}

    float asFloat() const override
    {
        return value;
    }

    void setValue(float value) override
    {
        this->value = value;
        onValueEvent.dispatchEvent(value);
    }

    void onValue(Callback<float>* listener) override
    {
        onValueEvent.attachListener(listener);
    }
};
