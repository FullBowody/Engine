#pragma once
#include <vector>
#include "Structs/Callback.hpp"

template <class T>
class ENGINE_API EventManager
{
private:
    std::vector<Callback<T>*> listeners;

public:
    EventManager()
    {

    }

    ~EventManager()
    {
        for (Callback<T>* listener : listeners)
            delete listener;
    }
    
    void dispatchEvent(const T& event)
    {
        for (Callback<T>* listener : listeners)
        {
            (*listener)(event);
        }
    }

    void attachListener(Callback<T>* listener)
    {
        if (listener != nullptr)
            listeners.push_back(listener);
    }

    void detachListener(Callback<T>* listener)
    {
        listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
    }
};