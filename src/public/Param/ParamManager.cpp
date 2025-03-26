#include "Params/ParamManager.hpp"

ParamManager::ParamManager()
{

}

ParamManager::~ParamManager()
{
    params.clear();
}

void ParamManager::registerParameter(std::shared_ptr<Param> param)
{
    if (param != nullptr)
        params.push_back(param);
}

std::weak_ptr<Param> ParamManager::getParameter(std::string name) const
{
    for (auto& param : params)
    {
        if (param->getName() == name)
            return param;
    }
    return std::weak_ptr<Param>();
}

const std::vector<std::shared_ptr<Param>>& ParamManager::getParameters() const
{
    return params;
}
