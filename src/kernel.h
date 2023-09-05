#ifndef KERNEL_H
#define KERNEL_H

#include "scheduler.h"
#include "cpu.h"
#include "process.h"

/**
 * @class Kernel
 * @brief Represents the system kernel, responsible for reading the file and
 * starting the scheduler.
 *
 */
class Kernel {
public:
    Kernel() : cpu() {
        processes_params = vector<ProcessParams *>();
    }

    explicit Kernel(vector<ProcessParams *> processes_params_) : cpu(),
                                     processes_params(processes_params) {}

    ~Kernel() {}

    void start(int scheduler_type) {
        scheduler = SchedulerFactory().create_scheduler(scheduler_type);
        start_scheduler();
    }

private:
    Scheduler scheduler;
    CPU cpu;
    std::vector<ProcessParams *> processes_params;

    // Reads standard file and sets a vector of processes params.


    // For each second of the system running, feeds the scheduler with the
    // processes that are ready to enter scheduling.
    void start_scheduler() {

        // Keeps track of the number of processes that have been created and
        // have been sent to the scheduler so that search for ready processes
        // can start from the last process that was created.
        int process_counter = 0;
        int time = 0;
        bool running = true;

        // Simulates the system running for each second.
        while (running) {
            // Creates a vector of processes that are ready to be processed.
            vector<Process> new_processes = create_processes(
                                                        time, process_counter);
            /* scheduler.feed(new_processes); TODO: Implement this */
            process_counter += new_processes.size();

            try
            {
                running = scheduler.run();
                // Only changes the state of the cpu if the scheduler has
                // not thrown a PreemptionException.
                cpu.change_state();
            }
            catch(const PreemptionException e)
            {
                cpu.handle_preemption(e.get_preempted_pid(),
                                        e.get_scheduled_pid());
            }
            ++time;
        }
    }

    // Returns a vector of processes that were required to be created at the
    // current time.
    vector<Process> create_processes(int current_time, int process_counter) {
        vector<Process> processes;
        for (int i = process_counter; i < processes_params.size(); i++)
        {
            if (processes_params[i]->get_creation_time() == current_time)
            {
                processes.push_back(
                    Process(
                        // Insert process params into the process.
                    ));
            }
        }
        return processes;
    }
};

class SchedulerFactory {
public:
    SchedulerFactory() {}

    ~SchedulerFactory() {}

    Scheduler create_scheduler(int scheduler_type) {
        switch (scheduler_type)
        {
        case FCFS:
            return FCFScheduler();
            break;
        case SJF:
            return SJFScheduler();
            break;
        case PNP:
            return PNPScheduler();
            break;
        case PP:
            return PPScheduler();
            break;
        case RR:
            return RRNPScheduler();
            break;
        default:
            return FCFScheduler();
            break;
        }
    }
};

#endif // KERNEL_H