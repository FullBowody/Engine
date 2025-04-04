#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include <functional>

class ActionThreadable
{
public:
    ActionThreadable();
    virtual ~ActionThreadable();

    /**
     * @brief Add an action to the queue. The action will be executed in running thread once the queue is executed.
     * @param action The action to be executed.
     * @note The action will be executed in the thread that calls executeActions().
     */
    void addAction(std::function<void()> action);

    /**
     * @brief Execute all actions in the queue. This will block until all actions are executed.
     * @note This function should be called in the thread that is responsible for executing the actions.
     * @note This function will clear the queue after executing all actions.
     */
    void executeActions();

    /**
     * @brief Clear all actions in the queue. This will not execute any actions.
     */
    void clearActions();

private:
    std::mutex action_mutex;
    std::queue<std::function<void()>> action_queue;
};
