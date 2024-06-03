#pragma once
#include <iostream>
#include <functional>
#include "utils.hpp"
#include "Struct/Nullable.hpp"

template <class T>
class Callback: public Nullable
{
protected:
    Callback() {}

public:
    virtual ~Callback() {}
    virtual void operator()(const T& data) = 0;
};

template <class T, class U>
class CallbackClass: public Callback<T>
{
private:
    U* obj;
    void (U::*func)(const T&);

public:
    CallbackClass(U* obj, void (U::*func)(const T&))
        : obj(obj), func(func) {}

    ~CallbackClass() {}

    void operator()(const T& data) override
    {
        (obj->*func)(data);
    }
};

template <class T>
class CallbackFunction: public Callback<T>
{
private:
    std::function<void(const T&)> func;

public:
    CallbackFunction(std::function<void(const T&)> func)
        : func(func) {}

    ~CallbackFunction() {}

    void operator()(const T& data) override
    {
        func(data);
    }
};
