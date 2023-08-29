#ifndef KERNEL_H
#define KERNEL_H

#include <list>
#include "scheduler.h"
#include "cpu.h"
#include "read_file.h"
#include "process.h"
#include "preemption_exception.h"

/**
 * @class Kernel
 * @brief Represents the system kernel, responsible for reading the file and
 * starting the scheduler.
 *
 */
class Kernel {
public:
    Kernel() {}

    ~Kernel() {}

    void start() {
        read_file();
        start_scheduler();
    }

private:
    Scheduler scheduler;
    CPU cpu;
    std::vector<ProcessParams *> processes_params;

    // Reads standard file and sets a vector of processes params.
    void read_file() {
        File f;
        f.read_file();
        processes_params = f.get_processes_params();
    }

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

    // Returns a list of processes that were required to be created at the
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

#endif // KERNEL_H