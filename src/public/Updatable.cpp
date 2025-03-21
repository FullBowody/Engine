#include "Updatable.hpp"

FBError Updatable::update(float dt)
{
    return onUpdate(dt);
}
