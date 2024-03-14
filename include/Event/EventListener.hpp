#pragma once
#include "Event.hpp"

template <class T=Event>
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
