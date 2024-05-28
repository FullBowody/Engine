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

    void operator()(const T& data) override
    {
        std::cout << "(obj->*func)(data);" << std::endl;
        (obj->*func)(data);
        std::cout << "(obj->*func)(data); [DONE]" << std::endl;
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

    void operator()(const T& data) override
    {
        std::cout << "func(data);" << std::endl;
        func(data);
        std::cout << "func(data); [DONE]" << std::endl;
    }
};
