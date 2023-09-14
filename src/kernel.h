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
    void start_scheduler(unsigned int scheduler_type, unsigned int quantum);

private:
    CPU cpu;
    Scheduler* scheduler;
    unsigned int number_of_processes;
    unsigned int process_counter;
    unsigned int current_time;
    unsigned int ran_pid; // pid of the process that ran in the last second.
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
    std::vector<Process*> create_processes();

    /**
     * @brief Prints the scheduling timeline header.
     */
    void setup_print();

    /**
     * @brief Prints the time stamp, followed by the state mneumonic for each
     * process of the process timeline.
     */
    void print_schedule(unsigned int current_time);

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

Kernel::Kernel() :
    cpu(CPU()),
    scheduler(nullptr),
    process_counter(0),
    current_time(0),
    ran_pid(0) {}

Kernel::Kernel(std::vector<ProcessParams *> processes_params) :
    cpu(CPU()),
    scheduler(nullptr),
    process_counter(0),
    current_time(0),
    ran_pid(0),
    params_queue(processes_params) {
        std::sort(
            params_queue.begin(),
            params_queue.end(),
            CompareProcessParams());
    }

Kernel::~Kernel() {}

void Kernel::start_scheduler(unsigned int scheduler_type, unsigned int quantum) {

    // Initializes the scheduler according to the scheduler type.
    scheduler = SchedulerFactory().create_scheduler(scheduler_type, quantum);

    number_of_processes = params_queue.size();
    bool running = process_counter < number_of_processes;

    if (running)
        setup_print();

    // Simulates the system running for each second.
    while (running) {

        // Creates a vector of processes that are ready to be processed.
        std::vector<Process*> new_processes = create_processes();
        scheduler->feed(new_processes);

        if (scheduler->has_preemption())
            cpu.handle_preemption(ran_pid,
                                    scheduler->get_current_pid());

        ran_pid = scheduler->run();
        if (ran_pid) {
            cpu.process(ran_pid);
            #ifndef DEBUG
            print_schedule(current_time);
            #endif
        }

        ++current_time;
        running = ran_pid || process_counter < number_of_processes;
    }
    reset_scheduler();
}

void Kernel::reset_scheduler() {
    delete scheduler;
    scheduler = nullptr;
    process_counter = 0;
    current_time = 0;
    ran_pid = 0;
    for (auto process = kernel_processes_vector.begin();
            process != kernel_processes_vector.end(); ++process)
        delete *process;
    kernel_processes_vector.clear();
}

std::vector<Process*> Kernel::create_processes() {
    std::vector<Process*> new_processes;
    while (process_counter < params_queue.size() &&
            params_queue[process_counter]->get_creation_time() == current_time) {
        ProcessParams* params = params_queue[process_counter];
        Process* new_p = new Process((process_counter+1),
                                 params->get_duration(),
                                 params->get_priority());
        kernel_processes_vector.push_back(new_p);
        new_processes.push_back(new_p);
        ++process_counter;
    }
    return new_processes;
}

void Kernel::setup_print() {
    std::cout << std::setw(3) << std::right << "" << "tempo"
            << std::setw(3) << std::left << "";
    for (std::size_t i = 1; i <= number_of_processes; i++) {
        std::string process_code = "P" + std::to_string(i);
        std::cout << std::setw(4) << std::right << process_code;
    }
    std::cout << std::endl;
}

void Kernel::print_schedule(unsigned int current_time) {
    std::cout << std::setw(5) << std::right << current_time << "-" << std::setw(5) << std::left << (current_time + 1);

    for (std::size_t i = 1; i <= number_of_processes; i++) {
        if (i <= kernel_processes_vector.size()) {
            std::cout << std::setw(4) << std::right
            << kernel_processes_vector[i - 1]->get_state();
        } else {
            std::cout << std::setw(5) << "  ";
        }
    }
    std::cout << std::endl;
}