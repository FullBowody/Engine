#pragma once
#include "Callback.hpp"

struct PromiseCallback
{
    ArgsCallback* resolve = nullptr;
    ArgsCallback* reject = nullptr;
    PromiseCallback() {}
    PromiseCallback(ArgsCallback* _resolve, ArgsCallback* _reject)
    {
        this->resolve = _resolve;
        this->reject = _reject;
    }
};

class Promise
{
private:
    PromiseCallback* promiseCallback = nullptr;
    ArgsCallback* resolveCallback = nullptr;
    ArgsCallback* rejectCallback = nullptr;

    void* resolveData = nullptr;
    void* rejectData = nullptr;

    unsigned char resolveCallCount = 0;
    unsigned char rejectCallCount = 0;

public:
    Promise(ArgsFunction callback)
    {
        init(new VoidArgsCallback(callback));
    }

    template<class T> Promise(T* _instance, void (T::*_callback)())
    {
        init(new TypedArgsCallback(_instance, _callback));
    }

    void init(ArgsCallback* callback);

    Promise* onResolve(ArgsFunction callback);
    template<class T> Promise* onResolve(T* _instance, void (T::*_callback)());

    Promise* onReject(ArgsFunction callback);
    template<class T> Promise* onReject(T* _instance, void (T::*_callback)());

    void _check_for_resolve(void* data);
    void _check_for_reject(void* data);
};