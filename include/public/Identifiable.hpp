#pragma once
#include <random>
#include "utils.hpp"

typedef unsigned long long ID;

class DLLExport Identifiable
{
private:
    ID m_id;

    virtual void setID(ID id);

protected:
    Identifiable() : m_id(Identifiable::getNewID()) {}

public:
    virtual ~Identifiable() {}

    static ID getNewID();
    virtual const ID getID() const;

    virtual bool operator==(const Identifiable& other) const;
    virtual bool operator!=(const Identifiable& other) const;
};
