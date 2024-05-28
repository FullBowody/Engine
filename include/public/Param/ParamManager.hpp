#pragma once
#include <vector>
#include "Param/Param.hpp"

class DLLExport ParamManager
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
