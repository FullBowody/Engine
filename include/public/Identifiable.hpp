#pragma once
#include "utils.hpp"

class Engine;

class DLLExport Identifiable
{
    friend Engine;

private:
    static int ID_COUNTER;
    int id;

    void setId(int id) { this->id = id; }

protected:
    Identifiable() : id(Identifiable::getNewId()) {}

public:
    static int getNewId() { return Identifiable::ID_COUNTER++; }

    int getId() const { return id; }
};
