#include "Structs/FBError.hpp"

FBError::FBError()
{
    code = OK;
}

FBError::FBError(int c)
{
    code = c;
}

FBError::operator int() const
{
    return code;
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
