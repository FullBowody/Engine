#pragma once
#include "utils.hpp"

class DLLExport FBError
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

    operator int() const;
    
    bool operator==(const FBError& other) const;
    bool operator!=(const FBError& other) const;
    friend std::ostream& operator<<(std::ostream& os, const FBError& e);
};
