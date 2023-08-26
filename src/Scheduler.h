#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <list>
#include "Process.h"

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
    Scheduler() {}

    virtual ~Scheduler() {}

    void run() {}

protected:
    std::list<Process> processList;   // A List of Processes

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