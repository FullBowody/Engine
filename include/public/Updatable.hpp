#pragma once
#include "utils.hpp"
#include "Structs/FBError.hpp"

class DLLExport Updatable
{
protected:
    virtual FBError onUpdate(float dt) = 0;\
    
public:
    Updatable() = default;
    virtual ~Updatable() = default;
    
    virtual FBError update(float dt);
};
