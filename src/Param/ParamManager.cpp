#include "Param/ParamManager.hpp"

ParamManager::ParamManager()
{

}

ParamManager::~ParamManager()
{
    for (Param* param : params)
        delete param;
}

void ParamManager::registerParameter(Param* param)
{
    if (param != nullptr)
        params.push_back(param);
}

Param* ParamManager::getParameter(std::string name) const
{
    for (Param* param : params)
    {
        if (param->getName() == name)
            return param;
    }
    return nullptr;
}

const std::vector<Param*>& ParamManager::getParameters() const
{
    return params;
}
