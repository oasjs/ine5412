#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <list>
#include "process.h"
#include "preemption_exception.h"

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

    virtual bool run() = 0;

    void feed(vector<Process> new_processes) {
        for (int i = 0; i < new_processes.size(); i++) {
            process_list.push_back(new_processes[i]);
        }
    }

private:
    std::list<Process> process_list;   // A List of Processes
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
        if (process_list.empty() && current_process.is_done()) {
            return false;
        }
        if (!current_process || current_process.is_done()) {
            current_process = process_list.pop_front();
        }
        current_process.run();
        return true;
    }
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

    void feed(vector<Process> new_processes) {
        // List of new processes is sorted, from the
        // element with the lowest duration, to the
        // highest duration
        std::sort(new_processes.begin(), new_processes.end(), compareByDuration);

        // Iterates the process_list
        // Inserts the new processes in
        // order, as it iterates
        for (int i = 0; i < process_list.size(); i++) {
            if (new_processes.empty()) {
                break;
            }

            if (compareByDuration(new_processes[0], process_list[i])) {
                process_list.insert(i, new_processes.pop_front());
            }
        }

        // For the processes that have
        // not been inserted before
        // They are now insert in the 
        // end of the vector
        if (!new_processes.empy()) {
            for (Process p : new_processes) {
                process_list.push_back(new_processes.pop_front())
            }
        }

    }

    bool run() override {
        if (process_list.empty() && current_process.is_done()) {
            return false;
        }
        if (!current_process || current_process.is_done()) {
            current_process = process_list.pop_front();
        }
        current_process.run();
        return true;
    }

private:
    bool compareByDuration(const Process& a, const Process& b) {
        return a.getDuration() < b.getDuration();
    }
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