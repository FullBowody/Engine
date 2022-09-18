#include "Promise.hpp"

Promise* _current_promise = nullptr;

void Promise::init(ArgsCallback* callback)
{
    _current_promise = this;
    callback->call(new PromiseCallback(
        new VoidArgsCallback([](void* data) { _current_promise->_check_for_resolve(data); }),
        new VoidArgsCallback([](void* data) { _current_promise->_check_for_reject(data); })
    ));
    _current_promise = nullptr;
}

void Promise::_check_for_resolve(void* data)
{
    this->resolveCallCount++;
    if (this->resolveData == nullptr)
        this->resolveData = data;

    if (this->resolveCallback != nullptr && this->resolveCallCount > 1)
        this->resolveCallback->call(this->resolveData);
}

void Promise::_check_for_reject(void* data)
{
    this->rejectCallCount++;
    if (this->rejectData == nullptr)
        this->rejectData = data;
        
    if (this->rejectCallback != nullptr && this->rejectCallCount > 1)
        this->rejectCallback->call(this->rejectData);
}

Promise* Promise::onResolve(void (*callback)(void*))
{
    this->resolveCallback = new VoidArgsCallback(callback);
    this->_check_for_resolve(nullptr);
    return this;
}

template<class T> Promise* Promise::onResolve(T* _instance, void (T::*_callback)())
{
    this->resolveCallback = new TypedArgsCallback(_instance, _callback);
    this->_check_for_resolve(nullptr);
    return this;
}

Promise* Promise::onReject(void (*callback)(void*))
{
    this->rejectCallback = new VoidArgsCallback(callback);
    this->_check_for_reject(nullptr);
    return this;
}

template<class T> Promise* Promise::onReject(T* _instance, void (T::*_callback)())
{
    this->rejectCallback = new TypedArgsCallback(_instance, _callback);
    this->_check_for_reject(nullptr);
    return this;
}