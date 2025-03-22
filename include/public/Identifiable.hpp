#pragma once
#include <random>
#include "utils.hpp"

typedef unsigned long long ID;

class ENGINE_API Identifiable
{
private:
    ID id;

    virtual void setID(ID id);

protected:
    Identifiable() : id(Identifiable::getNewID()) {}

public:
    virtual ~Identifiable() {}

    static ID getNewID();
    virtual const ID getID() const;

    virtual bool operator==(const Identifiable& other) const;
    virtual bool operator!=(const Identifiable& other) const;
};
