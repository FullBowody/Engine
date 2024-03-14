#pragma once

#include <string>
#include "EventData.hpp"

template <class T=EventData>
class Event
{
protected:
    const T& data;

    Event(const T& data)
        : data(data)
    {

    }

    ~Event()
    {
        
    }

    const T& getData() const
    {
        return data;
    }
};
