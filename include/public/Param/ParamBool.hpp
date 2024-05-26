#pragma once
#include "Param/Param.hpp"

class ParamBool: public Param
{
private:
    bool value;
    EventManager<bool> onValueEvent;

public:
    ParamBool(std::string name)
        : Param(name, ParamType::BOOL) {}

    ~ParamBool() {}

    bool asBool() const override
    {
        return value;
    }

    void setValue(bool value) override
    {
        this->value = value;
        onValueEvent.dispatchEvent(value);
    }

    void onValue(Callback<bool>* listener) override
    {
        onValueEvent.attachListener(listener);
    }
};
