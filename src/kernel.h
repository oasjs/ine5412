#ifndef KERNEL_H
#define KERNEL_H

#include <algorithm>
#include <vector>
#include <iomanip>
#include "cpu.h"
#include "scheduler.h"
#include "process.h"
#include "read_file.h"

/**
 * @class Kernel
 * @brief Represents the system system kernel.
 *
 */

class Kernel {
public:

    Kernel();

    Kernel(std::vector<ProcessParams *> processes_params);

    ~Kernel();

    /**
     * @brief Starts the scheduler. For each second of the system running, 
     * feeds the scheduler with the processes that are ready to enter 
     * scheduling.
     */
    void start_scheduler(unsigned long scheduler_type, unsigned long quantum);

private:
    CPU cpu;
    Scheduler* scheduler;
    unsigned long total_processes;
    unsigned long process_counter;
    std::vector<Process*> kernel_processes_vector;

    struct CompareProcessParams {
        bool operator()(const ProcessParams* lhs, const ProcessParams* rhs) const {
            return lhs->get_creation_time() < rhs->get_creation_time();
        }
    };
    std::vector<ProcessParams *> params_queue;

    /**
     * @brief Destroys the current scheduler and resets scheduling related
     * variables.
     */
    void reset_scheduler();

    /**
     * @brief Goes through the queue of process paramaters and creates the
     * processes that are ready to be created at the current time.
     * @return A vector<Process> containing the processes that were required to
     * be created at the current time.
     */
    std::vector<Process*> create_processes(unsigned long current_time);

    /**
     * @brief Prints the scheduling timeline header.
     */
    void setup_print();

    /**
     * @brief Prints the time stamp, followed by the state mneumonic for each
     * process of the process timeline.
     */
    void print_schedule(unsigned long current_time);

    /**
     * @brief Prints the statistics of the scheduling after the simulation is
     * complete.
     *
     * Prints the turnaround time for each process, the average turnaround time,
     * the average waiting time for each process and the number of context
     * changes.
     */
    void print_statistics();

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
    Scheduler* create_scheduler(unsigned long scheduler_type,
                                unsigned long quantum = 2) {
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

Kernel::Kernel() :
    cpu(CPU()),
    scheduler(nullptr),
    total_processes(0),
    process_counter(0),
    kernel_processes_vector(0) {}

Kernel::Kernel(std::vector<ProcessParams *> processes_params) :
    cpu(CPU()),
    scheduler(nullptr),
    total_processes(0),
    process_counter(0),
    kernel_processes_vector(0),
    params_queue(processes_params) {
        std::sort(
            params_queue.begin(),
            params_queue.end(),
            CompareProcessParams());
        kernel_processes_vector.reserve(params_queue.size());
    }

Kernel::~Kernel() {}

void Kernel::start_scheduler(unsigned long scheduler_type, unsigned long quantum) {

    total_processes = params_queue.size();
    unsigned long current_time = 0;
    unsigned long ran_pid = 0;

    // Initializes the scheduler according to the scheduler type.
    scheduler = SchedulerFactory().create_scheduler(scheduler_type, quantum);

    bool running = process_counter < total_processes;

    if (running)
        setup_print();

    // Simulates the system running for each second.
    while (running) {

        // Creates a vector of processes that are ready to be processed.
        std::vector<Process*> new_processes = create_processes(current_time);
        scheduler->feed(new_processes, current_time);

        // If the scheduler has preemption, handles it.
        if (scheduler->has_preemption(current_time)) {
            cpu.handle_preemption(ran_pid,
                                    scheduler->get_current_pid());
        }

        // Runs the scheduler for one second.
        ran_pid = scheduler->run(current_time);
        if (ran_pid) {
            cpu.process(ran_pid);
            #ifndef DEBUG
            print_schedule(current_time);
            #endif
        }

        ++current_time;
        running = ran_pid || process_counter < total_processes;
    }
    #ifndef DEBUG
    print_statistics();
    #endif
    reset_scheduler();
}

void Kernel::reset_scheduler() {
    delete scheduler;
    scheduler = nullptr;
    process_counter = 0;
    for (auto process = kernel_processes_vector.begin();
            process != kernel_processes_vector.end(); ++process)
        delete *process;
    kernel_processes_vector.clear();
}

std::vector<Process*> Kernel::create_processes(unsigned long current_time) {
    std::vector<Process*> new_processes;
    while (
        process_counter < params_queue.size() &&
        params_queue[process_counter]->get_creation_time() == current_time) {
        ProcessParams* params = params_queue[process_counter];
        Process* new_p = new Process((process_counter+1),
                                 params->get_duration(),
                                 params->get_priority(),
                                 current_time);
        kernel_processes_vector.push_back(new_p);
        if (params->get_duration() > 0)
            new_processes.push_back(new_p);
        ++process_counter;
    }
    return new_processes;
}

void Kernel::setup_print() {
    std::cout << std::setw(3) << std::right << "" << "tempo"
            << std::setw(3) << std::left << "";
    for (std::size_t i = 1; i <= total_processes; i++) {
        std::string process_code = "P" + std::to_string(i);
        std::cout << std::setw(4) << std::right << process_code;
    }
    std::cout << std::endl;
}

void Kernel::print_schedule(unsigned long current_time) {
    std::cout << std::setw(5) << std::right << current_time << "-" << std::setw(5) << std::left << (current_time + 1);

    for (std::size_t i = 1; i <= total_processes; i++) {
        if (i <= kernel_processes_vector.size()) {
            std::cout << std::setw(4) << std::right
            << kernel_processes_vector[i - 1]->get_state();
        } else {
            std::cout << std::setw(4) << "  ";
        }
    }
    std::cout << std::endl;
}

void Kernel::print_statistics() {
    float average_turnaround_time = 0;
    float average_waiting_time = 0;
    unsigned long context_changes = 0;

    std::cout << std::endl;
    std::cout << "Legenda: " << std::endl;
    std::cout << setw(2) << "" << "[TT] = Turnaround Time" << std::endl;
    std::cout << setw(2) << "" << "[WT] = Waiting Time" << std::endl;
    std::cout << setw(2) << "" << "[CC] = Context Changes" << std::endl;
    std::cout << std::endl;

    std::cout << "Estatísticas: " << std::endl;
    for (std::size_t i = 0; i < total_processes; i++) {
        Process* process = kernel_processes_vector[i];
        average_turnaround_time += process->get_turnaround_time();
        average_waiting_time += process->get_waiting_time();
        context_changes += process->get_context_changes();

        std::cout
        << std::setw(2) << std::right << "" << "P" << i+1 << ":"
        << std::setw(9) << std::left
                        << "[TT] "+to_string(process->get_turnaround_time())
        << std::setw(9) << std::left
                        << "[WT] "+to_string(process->get_waiting_time())
        << std::setw(9) << std::left
                        << "[CC] "+to_string(process->get_context_changes())
        << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Average turnaround time: "
        << average_turnaround_time / total_processes << std::endl;
    std::cout << std::endl;

    std::cout << "Average waiting time: "
        << average_waiting_time / total_processes << std::endl;
    std::cout << std::endl;

    std::cout << "Total context changes: " << context_changes << std::endl;
    std::cout << string(80, '-') << std::endl;

}