#pragma once
#include <functional>
#include "utils.hpp"

template <class T>
class DLLExport Callback
{
protected:
    Callback() {}

public:
    ~Callback() {}
    virtual void operator()(const T& data) = 0;
};

template <class T, class U>
class DLLExport CallbackClass: public Callback<T>
{
private:
    U* obj;
    void (U::*func)(const T&);

public:
    CallbackClass(U* obj, void (U::*func)(const T&))
        : obj(obj), func(func) {}

    ~CallbackClass() {}

    void operator()(const T& data)
    {
        (obj->*func)(data);
    }
};

template <class T>
class DLLExport CallbackFunction: public Callback<T>
{
private:
    std::function<void(const T&)> func;

public:
    CallbackFunction(std::function<void(const T&)> func)
        : func(func) {}

    ~CallbackFunction() {}

    void operator()(const T& data)
    {
        func(data);
    }
};
