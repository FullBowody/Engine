#pragma once
#include <vector>
#include "Params/Param.hpp"

class ENGINE_API ParamManager
{
private:
    std::vector<Param*> params;

public:
    ParamManager();
    ~ParamManager();

    void registerParameter(Param* param);
    
    virtual Param* getParameter(std::string name) const;
    virtual const std::vector<Param*>& getParameters() const;
};
