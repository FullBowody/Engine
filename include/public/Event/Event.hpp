#pragma once
#include <string>
#include "Event/EventData.hpp"

template <class T=EventData>
class Event
{
protected:
    Event(const T& data)
        : data(data)
    {
        std::cout << "> Storing in event address " << &data << " to " << &this->data << " as " << this << std::endl;
    }

    ~Event()
    {
        
    }

public:
    const T& data;
};
