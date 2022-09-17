#pragma once

/**
 * @brief Parent class, contains the [func] callback template
 */
class Callback
{
public:
    virtual void call() = 0;
};


/**
 * @brief Contains the type class method and instance 
 * @tparam T Type of the stored class
 */
template<class T>
class TypedCallback: public virtual Callback
{
private:
    void (T::*callback)();
    T* instance;
public:
    TypedCallback(void (T::*_callback)(), T* _instance)
    {
        this->callback = _callback;
        this->instance = _instance;
    }

    void call()
    {
        (this->instance->*this->callback)();
    }
};

/**
 * @brief Contains a void callback function
 */
class VoidCallback: public virtual Callback
{
private:
    void (*function)();
public:
    VoidCallback(void (*callback)())
    {
        this->function = callback;
    }

    void call()
    {
        this->function();
    }
};

/**
 * @brief Parent class, contains the [func] callback template
 */
class ArgsCallback
{
public:
    virtual void call(void* arg) = 0;
};


/**
 * @brief Contains the type class method and instance 
 * @tparam T Type of the stored class
 */
template<class T>
class TypedArgsCallback: public virtual ArgsCallback
{
private:
    void (T::*callback)(void*);
    T* instance;
public:
    TypedArgsCallback(void (T::*_callback)(void*), T* _instance)
    {
        this->instance = _instance;
        this->callback = _callback;
    }

    void call(void* args)
    {
        (this->instance->*this->callback)(args);
    }
};

/**
 * @brief Contains a void callback function
 */
class VoidArgsCallback: public virtual ArgsCallback
{
private:
    void (*function)(void*);
public:
    VoidArgsCallback(void (*callback)(void*))
    {
        this->function = callback;
    }

    void call(void* args)
    {
        this->function(args);
    }
};