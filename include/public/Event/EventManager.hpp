#pragma once
#include <vector>
#include "Event/Event.hpp"
#include "Event/EventListener.hpp"

template <class T=Event>
class EventManager
{
private:
    std::vector<EventListener<T>*> listeners;

protected:
    void dispatchEvent(const T& event)
    {
        std::cout << "> Dispatching event " << &event << " to " << listeners.size() << " listeners as " << this << std::endl;
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
        listeners.push_back(listener);
    }

    void detachListener(const EventListener<T>* listener)
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
