#pragma once
#include "utils.hpp"

class Engine;

typedef unsigned long long UUID;

class DLLExport Identifiable
{
    friend Engine;

private:
    UUID uuid;

    virtual void setUUID(UUID uuid);

protected:
    Identifiable() : uuid(Identifiable::getNewUUID()) {}

public:
    virtual ~Identifiable() {}

    static UUID getNewUUID();
    virtual const UUID getUUID() const;

    virtual bool operator==(const Identifiable& other) const;
    virtual bool operator!=(const Identifiable& other) const;
};
