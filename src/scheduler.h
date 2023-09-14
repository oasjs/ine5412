#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <iostream>
#include "process.h"
#include "process_queue.h"

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
        init_process = new Process();
        current_process = init_process;
    }

    virtual ~Scheduler() {}

    /**
     * @brief Runs the scheduler for one second.
     *
     * The scheduler will run the current process for one second.
     * If the process is done, it will be removed from the queue
     * and the next process will be executed.
     *
     * @return The pid of the process that was executed.
     */
    unsigned long run() {
        if (process_queue->empty() && current_process->is_done()) {
            return 0;
        }
        if (current_process->is_done()) {
            current_process->set_state(DONE);
            current_process = process_queue->front();
            process_queue->pop();
        }
        current_process->set_state(RUNNING);
        current_process->run();
        return current_process->get_pid();
    }

    /**
     * @brief Feeds the scheduler with new processes.
     *
     * @param new_processes The new processes to be fed.
     */
    void feed(std::vector<Process*> new_processes) {
        for (auto process : new_processes) {
            process->set_state(READY);
            process_queue->push(process);
        }
    }

    /**
     * @brief Returns the pid of the current process.
     *
     * @return The pid of the current process.
     */
    unsigned long get_current_pid() {
        return current_process->get_pid();
    }

    /**
     * @brief Implements preemption according to the scheduler type.
     * Attributes the current process as the preempting process and inserts
     * the preempted process back in queue.
     *
     * @return True if the scheduler has preemption. False otherwise.
     */
    virtual bool has_preemption() = 0;

protected:
    Process* init_process;
    Process* current_process;
    ProcessQueueWrapper *process_queue;

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
    FCFScheduler() : Scheduler() {
        process_queue = new ProcessQueue();}

    ~FCFScheduler() {
        delete init_process;
        delete process_queue;
    }

    bool has_preemption() {
        return false;}

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
private:
    struct CompareProcess {
        bool operator()(Process* const& p1, Process* const& p2) {
            return p1->get_duration() > p2->get_duration();
        }
    };
    CompareProcess c;

public:
    SJFScheduler() : Scheduler() {
        process_queue = new PriorityProcessQueue<CompareProcess>(c);}

    ~SJFScheduler() {
        delete process_queue;
        delete init_process;
    }

    bool has_preemption() {
        return false; }

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
private:
    struct CompareProcess {
        bool operator()(Process* const& p1, Process* const& p2) {
            return p1->get_priority() < p2->get_priority();
        }
    };
    CompareProcess c;

public:
    PNPScheduler() : Scheduler() {
        process_queue = new PriorityProcessQueue<CompareProcess>(c);}

    ~PNPScheduler() {
        delete process_queue;
        delete init_process;
    }

    bool has_preemption() {
        return false; }

};

/**
 * @class PPScheduler
 * @brief Specialyze the Priority, with preemption Scheduler.
 *
 * The 
 *
 */
class PPScheduler : public PNPScheduler {
public:
    bool has_preemption() {
        if (!current_process->is_done() && !process_queue->empty()) {
            if (current_process->get_priority() <
                process_queue->front()->get_priority()
                ) {
                process_queue->push(current_process);
                current_process->set_state(READY);
                current_process = process_queue->front();
                process_queue->pop();
                return true;
            }
        }
        return false;
    }
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
private:
    unsigned long quantum;

public:
    RRNPScheduler(unsigned long q) : Scheduler(), quantum(q) {
        process_queue = new ProcessQueue();}

    ~RRNPScheduler() {
        delete init_process;
        delete process_queue;
    }

    bool has_preemption() {
        if (!current_process->is_done() && !process_queue->empty()) {
            if (current_process->get_total_execution_time() % quantum == 0) {
                process_queue->push(current_process);
                current_process->set_state(READY);
                current_process = process_queue->front();
                process_queue->pop();
                return true;
            }
        }
        return false;
    }

};

#endif // SCHEDULER_H