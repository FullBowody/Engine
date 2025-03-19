#pragma once
#include "utils.hpp"
#include "Structs/FBError.hpp"

class DLLExport Updatable
{
public:
    Updatable() = default;
    virtual FBError update(float dt);

    virtual ~Updatable() = default;

protected:
    virtual FBError onUpdate(float dt) = 0;
};

Updatable::Updatable()
{
}

Updatable::~Updatable()
{
}

FBError Updatable::update(float dt)
{
    return onUpdate(dt);
}
