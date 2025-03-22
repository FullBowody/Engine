#pragma once
#include <sstream>

#if (defined WIN32 || defined _WIN32 || defined WINCE)
    #ifdef EXPORT_ENGINE
        # define ENGINE_API __declspec(dllexport)
    #else
        # define ENGINE_API __declspec(dllimport)
    #endif
#else
    #ifdef EXPORT_ENGINE
        # define ENGINE_API __attribute__((visibility("default")))
    #else
        # define ENGINE_API
    #endif
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
