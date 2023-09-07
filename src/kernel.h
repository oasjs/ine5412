#ifndef KERNEL_H
#define KERNEL_H

#include <vector>
#include "scheduler.h"
#include "cpu.h"
#include "process.h"
#include "read_file.h"

/**
 * @class Kernel
 * @brief Represents the system kernel, responsible for reading the file and
 * starting the scheduler.
 *
 */

class Kernel {
public:

    Kernel ();

    ~Kernel();

    void start(int scheduler_type,
                std::vector<ProcessParams *> processes_params);

private:
    CPU cpu;
    Scheduler* scheduler;
    unsigned int process_counter;

    // For each second of the system running, feeds the scheduler with the
    // processes that are ready to enter scheduling.
    void start_scheduler();

    // Returns a vector of processes that were required to be created at the
    // current time.
    std::vector<Process> create_processes(unsigned int current_time);

    struct CompareProcessParams {
        bool operator()(const ProcessParams* lhs, const ProcessParams* rhs) const {
            return lhs->get_creation_time() > rhs->get_creation_time();
        }
    };
    std::priority_queue<ProcessParams*, std::vector<ProcessParams*>,
                        CompareProcessParams> params_queue;
};

enum SchedulerType {
    FCFS = 1,
    SJF,
    PNP,
    PP,
    RR
};

class SchedulerFactory {
public:
    SchedulerFactory() {}

    ~SchedulerFactory() {}

    Scheduler* create_scheduler(unsigned int scheduler_type) {
        switch (scheduler_type)
        {
        case FCFS:
            return new FCFScheduler();
            break;
        case SJF:
            return new SJFScheduler();
            break;
        /* case PNP:
            return new PNPScheduler();
            break;
        case PP:
            return new PPScheduler();
            break;
        case RR:
            return new RRNPScheduler();
            break; */
        default:
            return new FCFScheduler();
            break;
        }
    }
};

#endif // KERNEL_H


Kernel::Kernel() {
        cpu = CPU();
    }

Kernel::~Kernel() {}

void Kernel::start(int scheduler_type,
                    std::vector<ProcessParams *> processes_params) {

    // Creates a priority queue of processes params, ordered by creation time.
    params_queue = std::priority_queue<ProcessParams*,
                    std::vector<ProcessParams*>,
                    CompareProcessParams>(  processes_params.begin(),
                                            processes_params.end());

    // Initializes the scheduler according to the scheduler type.
    scheduler = SchedulerFactory().create_scheduler(scheduler_type);
    start_scheduler();
}

void Kernel::start_scheduler() {

    process_counter = 0;
    unsigned int time = 0;
    bool running = true;

    // Simulates the system running for each second.
    while (running) {

        // Creates a vector of processes that are ready to be processed.
        std::vector<Process> new_processes = create_processes(time);
        scheduler->feed(new_processes);

        try
        {
            running = scheduler->run();
            // Only changes the state of the cpu if the scheduler has not thrown
            // a PreemptionException.
            cpu.change_state();
        }
        catch(const exception e)
        {
            // cpu.handle_preemption(e.get_preempted_pid(),
            //                         e.get_scheduled_pid());
        }
        ++time;
    }
}

std::vector<Process> Kernel::create_processes(unsigned int current_time) {
    std::vector<Process> processes;
    while (!params_queue.empty() &&
            params_queue.top()->get_creation_time() == current_time) {
        ProcessParams* params = params_queue.top();
        params_queue.pop();
        processes.push_back(Process(process_counter,
                                    params->get_duration(),
                                    params->get_priority()));
        ++process_counter;
    }
    return processes;
}