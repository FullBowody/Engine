#pragma once
#include <vector>
#include "Param/Param.hpp"

class DLLExport ParamManager
{
private:
    std::vector<Param*> params;

public:
    ParamManager()
    {

    }

    ~ParamManager()
    {
        std::cout << "ParamManager::~ParamManager()" << std::endl;
        for (Param* param : params)
            delete param;
        std::cout << "ParamManager::~ParamManager() [DONE]" << std::endl;
    }

    void registerParameter(Param* param)
    {
        if (param != nullptr)
            params.push_back(param);
    }

    Param* getParameter(std::string name) const
    {
        for (Param* param : params)
        {
            if (param->getName() == name)
                return param;
        }
        return nullptr;
    }

    const std::vector<Param*>& getParameters() const
    {
        return params;
    }
};
