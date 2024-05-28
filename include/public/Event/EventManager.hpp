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
        std::cout << "EventManager::~EventManager()" << std::endl;
        for (Callback<T>* listener : listeners)
            delete listener;
        std::cout << "EventManager::~EventManager() [DONE]" << std::endl;
    }
    
    void dispatchEvent(const T& event)
    {
        for (Callback<T>* listener : listeners)
        {
            std::cout << "EventManager::dispatchEvent" << std::endl;
            (*listener)(event);
            std::cout << "EventManager::dispatchEvent [DONE]" << std::endl;
        }
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
