#include "Structs/Identifiable.hpp"
#include <random>

void Identifiable::setUUID(UUID uuid)
{
    this->m_uuid = uuid;
}

UUID Identifiable::getNewUUID()
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<UUID> dis(0, std::numeric_limits<UUID>::max());
    return dis(gen);
}

const UUID Identifiable::getUUID() const
{
    return this->m_uuid;
}

bool Identifiable::operator==(const Identifiable& other) const
{
    return this->m_uuid == other.m_uuid;
}

bool Identifiable::operator!=(const Identifiable& other) const
{
    return this->m_uuid != other.m_uuid;
}
