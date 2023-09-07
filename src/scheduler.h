#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <iostream>
#include "process.h"

/**
 * @class Scheduler
 * @brief Abstract Class that represent the Scheduler.
 *
 * This class will be Specialized depending on each
 * different type of scheduling
 *
 */
class Scheduler {
public:
    Scheduler() {
        current_process = Process();
    }

    virtual ~Scheduler() {}

    virtual bool run() = 0;

    virtual void feed(std::vector<Process> new_processes) = 0;

    bool triggers_preemption() {
        return false;
    }

protected:
    Process current_process;

    /**
     * The function that is going to print the Schedule
     * 
     */
    void printSchedule() {
        std::cout << "Generic: " << std::endl;  // TODO
    }
};

/**
 * @class FCFScheduler
 * @brief Specialyze the First Come, First Served Scheduler.
 *
 * The first process that comes is the first process that
 * is processed by the CPU, followed by the others in
 * sequence.
 *
 */
class FCFScheduler : public Scheduler {
public:
    FCFScheduler() {}

    ~FCFScheduler() {}

    bool run() override {
        if (process_queue.empty() && current_process.is_done()) {
            return false;
        }
        if (!current_process.get_duration() || current_process.is_done()) {
            current_process = process_queue.front();
            process_queue.pop();
        }
        current_process.run();
        return true;
    }

    void feed(std::vector<Process> new_processes) override {
        for (auto process : new_processes) {
            process_queue.push(process);
        }
    }

private:
    std::queue<Process> process_queue;

};

/**
 * @class SJFScheduler
 * @brief Specialyze the Shortest Job Firts Scheduler.
 *
 * The job with the shortest duration is processed
 * first.
 *
 */
class SJFScheduler : public Scheduler {
public:
    SJFScheduler() {}

    ~SJFScheduler() {}

    bool run() override {
        if (process_queue.empty() && current_process.is_done()) {
            return false;
        }
        if (!current_process.get_duration() || current_process.is_done()) {
            current_process = process_queue.top();
            process_queue.pop();
        }
        current_process.run();
        return true;
    }

    void feed(std::vector<Process> new_processes) override {
        for (auto process : new_processes) {
            process_queue.push(process);
        }
    }

private:
    struct CompareProcess {
        bool operator()(Process const& p1, Process const& p2) {
            return p1.get_duration() > p2.get_duration();
        }
    };
    std::priority_queue<Process, std::vector<Process>, CompareProcess> process_queue;



};

// Specialization PNPScheduler
/**
 * @class PNPScheduler
 * @brief Specialyze the Priority, without preemption Scheduler.
 *
 * The jobs are ordered by priority and processed by this
 * order
 *
 */
class PNPScheduler : public Scheduler {
public:
    PNPScheduler() {}

    ~PNPScheduler() {}

};

/**
 * @class PPScheduler
 * @brief Specialyze the Priority, with preemption Scheduler.
 *
 * The 
 *
 */
class PPScheduler : public Scheduler {
public:
    PPScheduler() {}

    ~PPScheduler() {}

};

/**
 * @class RRNPScheduler
 * @brief Specialyze the Round-robin without preemption Scheduler.
 *
 * Each process is execute by a determined time
 * and when the time is finished the next process
 * (quantum)is executed. This cycle continue until
 * all of the processes have been done
 *
 */
class RRNPScheduler : public Scheduler {
public:
    RRNPScheduler() {}

    ~RRNPScheduler() {}

};

#endif // SCHEDULER_H