#pragma once
#include "utils.hpp"

class Engine;

class DLLExport Identifiable
{
    friend Engine;

private:
    static int ID_COUNTER;
    int id;

    virtual void setId(int id);

protected:
    Identifiable() : id(Identifiable::getNewId()) {}

public:
    static int getNewId();

    virtual int getId() const;
};
