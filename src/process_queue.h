#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

#include <queue>
#include "process.h"

/**
 * @class ProcessQueueWrapper
 * @brief Wrapper for the process queue. This is used to make the scheduler
 * independent of the queue implementation.
 */
class ProcessQueueWrapper {
public:
    virtual void push(Process process) = 0;

    virtual Process front() = 0;

    virtual void pop() = 0;

    virtual bool empty() = 0;

    virtual std::size_t size() = 0;
};


class ProcessQueue : public ProcessQueueWrapper {
public:
    ProcessQueue() {}

    void push(Process process) {
        queue.push(process);
    }

    Process front() {
        return queue.front();
    }

    void pop() {
        queue.pop();
    }

    bool empty() {
        return queue.empty();
    }

    std::size_t size() {
        return queue.size();
    }

private:
    std::queue<Process> queue;
};

template<typename Comparator>
class PriorityProcessQueue : public ProcessQueueWrapper {
private:
    std::priority_queue<Process, std::vector<Process>, Comparator> queue;

public:
    PriorityProcessQueue(const Comparator& c) : queue(c) {}

    void push(Process process) {
        queue.push(process);
    }

    Process front() {
        return queue.top();
    }

    void pop() {
        queue.pop();
    }

    bool empty() {
        return queue.empty();
    }

    std::size_t size() {
        return queue.size();
    }

};

#endif
