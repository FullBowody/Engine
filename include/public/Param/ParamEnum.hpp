#pragma once
#include "Param/Param.hpp"

class DLLExport ParamEnum: public Param
{
private:
    int value;
    EventManager<int> onValueEvent;
    std::vector<std::string> options;

public:
    ParamEnum(std::string name)
        : Param(name, ParamType::ENUM) {}

    ~ParamEnum() {}

    int asEnum() const override
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

    void addOption(std::string option)
    {
        options.push_back(option);
    }

    const std::vector<std::string>& getOptions() const
    {
        return options;
    }
};
