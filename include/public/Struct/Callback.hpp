#pragma once
#include <iostream>
#include <functional>
#include "utils.hpp"

template <class T>
class DLLExport Callback
{
protected:
    Callback() {}

public:
    virtual ~Callback() {}
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

    virtual void operator()(const T& data) override
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

    virtual void operator()(const T& data) override
    {
        func(data);
    }
};
