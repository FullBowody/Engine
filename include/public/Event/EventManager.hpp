#pragma once
#include <vector>
#include <functional>

template <class T>
class EventManager
{
private:
    std::vector<std::function<void(const T&)>> listeners;

public:
    EventManager()
    {

    }

    ~EventManager()
    {
        listeners.clear();
    }
    
    void dispatchEvent(const T& event)
    {
        for (auto& listener : listeners)
        {
            listener(event);
        }
    }

    void addEventListener(std::function<void(const T&)> listener)
    {
        listeners.push_back(listener);
    }

    void removeEventListener(std::function<void(const T&)> listener)
    {
        listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
            [&listener](const std::function<void(const T&)>& l) {
                return l.target<void(const T&)>() == listener.target<void(const T&)>();
            }), listeners.end());
    }
};
