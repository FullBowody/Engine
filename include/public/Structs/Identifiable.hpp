#pragma once
#include "utils.hpp"

typedef unsigned long long UUID;

class DLLExport Identifiable
{
private:
    UUID m_uuid;

    virtual void setUUID(UUID uuid);

protected:
    Identifiable() : m_uuid(Identifiable::getNewUUID()) {}

public:
    virtual ~Identifiable() {}

    static UUID getNewUUID();
    virtual const UUID getUUID() const;

    virtual bool operator==(const Identifiable& other) const;
    virtual bool operator!=(const Identifiable& other) const;
};
