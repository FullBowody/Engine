#pragma once
#include "utils.hpp"

class DLLExport FBError
{
private:
    int code;

public:
    static const int OK = 0;

    FBError();
    FBError(const FBError& other);
    FBError(int c);

    operator int() const;
    
    FBError& operator=(const FBError& other);
    bool operator==(const FBError& other) const;
    bool operator!=(const FBError& other) const;
    friend std::ostream& operator<<(std::ostream& os, const FBError& e);
};

FBError::FBError()
{
    code = OK;
}

FBError::FBError(const FBError& other)
{
    code = other.code;
}

FBError::FBError(int c)
{
    code = c;
}

FBError::operator int() const
{
    return code;
}

FBError& FBError::operator=(const FBError& other)
{
    code = other.code;
    return *this;
}

bool FBError::operator==(const FBError& other) const
{
    return code == other.code;
}

bool FBError::operator!=(const FBError& other) const
{
    return code != other.code;
}

std::ostream& operator<<(std::ostream& os, const FBError& e)
{
    os << e.code;
    return os;
}
