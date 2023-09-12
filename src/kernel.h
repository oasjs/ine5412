#ifndef KERNEL_H
#define KERNEL_H

#include <vector>
#include "scheduler.h"
#include "cpu.h"
#include "process.h"
#include "process.h"
#include "read_file.h"

/**
 * @class Kernel
 * @brief Represents the system system kernel.
 *
 */

class Kernel {
public:

    Kernel ();

    ~Kernel();

    /**
     * @brief Starts the kernel. Creates the process parameters priority queue
     * instantiates the scheduler and calls start_scheduler().
     */
    void start(int scheduler_type,
                std::vector<ProcessParams *> processes_params);

private:
    CPU cpu;
    Scheduler* scheduler;
    unsigned int process_counter;
    unsigned int current_time;
    unsigned int ran_pid; // pid of the process that ran in the last second.

    /**
     * @brief Starts the scheduler. For each second of the system running, 
     * feeds the scheduler with the processes that are ready to enter 
     * scheduling.
     */
    void start_scheduler();

    /**
     * @brief Goes through the queue of process paramaters and creates the
     * processes that are ready to be created at the current time.
     * @return A vector<Process> containing the processes that were required to
     * be created at the current time.
     */
    std::vector<Process> create_processes();


    struct CompareProcessParams {
        bool operator()(const ProcessParams* lhs, const ProcessParams* rhs) const {
            return lhs->get_creation_time() >= rhs->get_creation_time();
        }
    };
    /**
     * @brief A priority queue of process parameters, ordered by creation time.
     */
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

    /**
     * @brief Creates a scheduler according to the scheduler type.
     * @param scheduler_type The type of scheduler to be created.
     * @param quantum The quantum of the scheduler, if it is a Round Robin
     * scheduler. Defaults to 2.
     * @return A pointer to the created scheduler.
     */
    Scheduler* create_scheduler(unsigned int scheduler_type,
                                unsigned int quantum = 2) {
        switch (scheduler_type)
        {
        case FCFS:
            return new FCFScheduler();
            break;
        case SJF:
            return new SJFScheduler();
            break;
        case PNP:
            return new PNPScheduler();
            break;
        case PP:
            return new PPScheduler();
            break;
        case RR:
            return new RRNPScheduler(quantum);
            break;
        default:
            return new FCFScheduler();
            break;
        }
    }
};

#endif // KERNEL_H


Kernel::Kernel() :  cpu(CPU()),
                    scheduler(nullptr),
                    current_time(0),
                    process_counter(0) {}

Kernel::~Kernel() {
    delete scheduler;
}

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

    if (scheduler == nullptr)
        return;

    process_counter = 1;
    ran_pid = 1;
    bool running = ran_pid || !params_queue.empty();

    // Simulates the system running for each second.
    while (running) {

        // Creates a vector of processes that are ready to be processed.
        std::vector<Process> new_processes = create_processes();
        scheduler->feed(new_processes);

        if (scheduler->has_preemption())
            cpu.handle_preemption(ran_pid,
                                    scheduler->get_current_pid());

        ran_pid = scheduler->run();
        if (ran_pid)
            cpu.process(ran_pid);
        // scheduler->printSchedule(current_time);
        std::cout << "Time: " << current_time << " PID: " << ran_pid << std::endl;
        ++current_time;
        running = ran_pid || !params_queue.empty();
    }
}

std::vector<Process> Kernel::create_processes() {
    std::vector<Process> processes;
    while (!params_queue.empty() &&
            params_queue.top()->get_creation_time() == current_time) {
        ProcessParams* params = params_queue.top();
        params_queue.pop();
        processes.push_back(Process((process_counter),
                                    params->get_duration(),
                                    params->get_priority()));
        ++process_counter;
    }
    return processes;
}