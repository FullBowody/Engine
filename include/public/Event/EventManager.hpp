#pragma once
#include <vector>
#include <functional>

template <class T>
using EventListener = std::function<void(const T&)>;

template <class T>
class EventManager
{
private:
    std::vector<EventListener<T>> listeners;

protected:
    void dispatchEvent(const T& event)
    {
        for (EventListener<T> listener : listeners)
            listener(event);
    }

public:
    EventManager()
    {

    }

    ~EventManager()
    {

    }


    void attachListener(EventListener<T> listener)
    {
        if (listener != nullptr)
            listeners.push_back(listener);
    }

    void detachListener(EventListener<T> listener)
    {
        for (auto it = listeners.begin(); it != listeners.end(); it++)
        {
            if (*it == listener)
            {
                listeners.erase(it);
                break;
            }
        }
    }
};
