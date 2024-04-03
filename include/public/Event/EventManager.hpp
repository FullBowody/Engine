#pragma once
#include <vector>
#include <iostream>
#include "Event/Event.hpp"
#include "Event/EventListener.hpp"

template <class T>
class EventManager
{
private:
    std::vector<EventListener<T>*> listeners;

protected:
    void dispatchEvent(const T& event)
    {
        std::cout << "dispatch to " << listeners.size() << " listeners" << std::endl;
        for (auto listener : listeners)
        {
            listener->onEvent(event);
        }
    }

public:
    EventManager()
    {

    }

    ~EventManager()
    {

    }


    void attachListener(EventListener<T>* listener)
    {
        std::cout << "void attachListener(EventListener<T>* listener)" << std::endl;
        listeners.push_back(listener);
        std::cout << "listeners.size() = " << listeners.size() << std::endl;
    }

    void detachListener(const EventListener<T>* listener)
    {
        std::cout << "void detachListener(const EventListener<T>* listener)" << std::endl;
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
