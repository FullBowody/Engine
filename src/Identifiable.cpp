#include "Identifiable.hpp"

int Identifiable::ID_COUNTER = 0;

void Identifiable::setId(int id)
{
    this->id = id;
}

int Identifiable::getNewId()
{
    return Identifiable::ID_COUNTER++;
}

int Identifiable::getId() const
{
    return id;
}
