#pragma once
#include <string>
#include "Event/EventData.hpp"

template <class T=EventData>
class Event
{
protected:
    T data;

    Event(const T& data)
        : data(data)
    {
        
    }

    Event(const Event& event)
        : data(event.data)
    {
        
    }

    ~Event()
    {
        
    }

public:
    const T& getData() const
    {
        return data;
    }
};
