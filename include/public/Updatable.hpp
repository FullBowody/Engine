#pragma once
#include "utils.hpp"

class DLLExport Updatable
{
public:
    virtual int update(float dt) = 0;
};
