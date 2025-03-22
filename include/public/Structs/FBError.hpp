#pragma once
#include "utils.hpp"

class ENGINE_API FBError
{
private:
    int code;

public:
    enum ErrorCode {
        OK = 0,
        NO_CAPTURE_DEVICE,
        NO_CAMERA,
        NO_MARKER,
        NO_CAPTURE,
    };

    FBError();
    FBError(int c);

    virtual operator int() const;
    
    virtual bool operator==(const FBError& other) const;
    virtual bool operator!=(const FBError& other) const;
    friend std::ostream& operator<<(std::ostream& os, const FBError& e);
};
