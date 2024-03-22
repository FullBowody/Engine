#pragma once
#include "Event/Event.hpp"

template <class T>
class EventListener
{
private:
    
public:
    EventListener()
    {

    }

    ~EventListener()
    {

    }


    virtual void onEvent(const T& event) = 0;
};
