#include "Identifiable.hpp"

void Identifiable::setID(ID id)
{
    this->id = id;
}

ID Identifiable::getNewID()
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<ID> dis(0, std::numeric_limits<ID>::max());
    return dis(gen);
}

const ID Identifiable::getID() const
{
    return id;
}

bool Identifiable::operator==(const Identifiable& other) const
{
    return id == other.id;
}

bool Identifiable::operator!=(const Identifiable& other) const
{
    return id != other.id;
}
