#include "ActionThreadable.hpp"

ActionThreadable::ActionThreadable()
{
}

ActionThreadable::~ActionThreadable()
{
    clearActions();
}

void ActionThreadable::addAction(std::function<void()> action)
{
    std::lock_guard<std::mutex> lock(action_mutex);
    action_queue.push(action);
}

void ActionThreadable::executeActions()
{
    std::lock_guard<std::mutex> lock(action_mutex);
    while (!action_queue.empty())
    {
        auto action = action_queue.front();
        action_queue.pop();
        action();
    }
}

void ActionThreadable::clearActions()
{
    std::lock_guard<std::mutex> lock(action_mutex);
    while (!action_queue.empty())
    {
        action_queue.pop();
    }
}
