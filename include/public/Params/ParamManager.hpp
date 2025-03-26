#pragma once
#include <vector>
#include <memory>
#include "Params/Param.hpp"

class ENGINE_API ParamManager
{
private:
    std::vector<std::shared_ptr<Param>> params;

public:
    ParamManager();
    ~ParamManager();

    void registerParameter(std::shared_ptr<Param> param);
    
    virtual std::weak_ptr<Param> getParameter(std::string name) const;
    virtual const std::vector<std::shared_ptr<Param>>& getParameters() const;
};
