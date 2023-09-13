#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

#include <queue>
#include "process.h"

class ProcessQueueWrapper {
public:
    virtual ~ProcessQueueWrapper() {}

    virtual void push(Process* process) = 0;

    virtual Process* front() = 0;

    virtual void pop() = 0;

    virtual bool empty() = 0;

    virtual std::size_t size() = 0;
};

class ProcessQueue : public ProcessQueueWrapper {
public:
    void push(Process* process) override {
        queue.push(process);
    }

    Process* front() override {
        if (!queue.empty()) {
            return queue.front();
        }
        return nullptr; // Return nullptr if the queue is empty
    }

    void pop() override {
        if (!queue.empty()) {
            queue.pop();
        }
    }

    bool empty() override {
        return queue.empty();
    }

    std::size_t size() override {
        return queue.size();
    }

private:
    std::queue<Process*> queue;
};

template <typename Comparator>
class PriorityProcessQueue : public ProcessQueueWrapper {
private:
    std::priority_queue<Process*, std::vector<Process*>, Comparator> queue;

public:
    PriorityProcessQueue(const Comparator& c) : queue(c) {}

    void push(Process* process) override {
        queue.push(process);
    }

    Process* front() override {
        if (!queue.empty()) {
            return queue.top();
        }
        return nullptr; // Return nullptr if the queue is empty
    }

    void pop() override {
        if (!queue.empty()) {
            queue.pop();
        }
    }

    bool empty() override {
        return queue.empty();
    }

    std::size_t size() override {
        return queue.size();
    }
};

#endif
