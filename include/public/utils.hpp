#pragma once
#include <sstream>

#if (defined WIN32 || defined _WIN32 || defined WINCE)
    #ifdef EXPORT_ENGINE
        # define DLLExport __declspec(dllexport)
    #else
        # define DLLExport __declspec(dllimport)
    #endif
#else
# define DLLExport
#endif

#define CHECK_ERRORS(x) \
{ \
    auto res = x; \
    if (res) return res; \
}

template <typename T>
std::string printPtr(T* ptr)
{
    if (ptr == nullptr)
        return "null";
    std::ostringstream oss;
    oss << *ptr;
    return oss.str();
}
