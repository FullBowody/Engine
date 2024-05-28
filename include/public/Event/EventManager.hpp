#pragma once
#include <vector>
#include "Struct/Callback.hpp"

template <class T>
class DLLExport EventManager
{
private:
    std::vector<Callback<T>*> listeners;

public:
    EventManager()
    {

    }

    ~EventManager()
    {
        std::cout << "EventManager destructor" << std::endl;
        for (Callback<T>* listener : listeners)
            delete listener;
    }
    
    void dispatchEvent(const T& event)
    {
        for (Callback<T>* listener : listeners)
            (*listener)(event);
    }

    void attachListener(Callback<T>* listener)
    {
        if (listener != nullptr)
            listeners.push_back(listener);
    }

    // TODO : Modify this to use listener id (returned from attachListener)
    // void detachListener(Callback<T>* listener)
    // {
    //     for (auto it = listeners.begin(); it != listeners.end(); it++)
    //     {
    //         if (*it == listener)
    //         {
    //             listeners.erase(it);
    //             break;
    //         }
    //     }
    // }
};
