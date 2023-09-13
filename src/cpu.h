#ifndef CPU_H
#define CPU_H

#include <vector>
#include <random>
#include "context.h"
#include "memory.h"

/**
 * @class CPU
 * @brief Represents the CPU and its contents.
 *
 */
class CPU {
public:
    CPU() {
        registers = std::vector<unsigned int>(6);
        sp = 0;
        pc = 0;
        st = 0;
    }

    ~CPU() {}

    /**
     * @brief Processes a process. If the process was already running, it will
     * continue to run. Otherwise, it will load the context of the process.
     * @param pid The id of the current process.
     */
    void process(unsigned int pid) {

        // If the process was already running, it will continue to run.
        // This simulates the process being ran.
        if (pid == registers[0]) {
            // Prepares to generate a random number.
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 100);

            // Sets each information of the cpu state to a random number.
            for (int n = 1; n < 6; ++n) {
                registers[n] = dis(gen);
            }
            sp = dis(gen);
            pc = dis(gen);
            st = dis(gen);
        // Otherwise, try to load the context of the process.
        } else {
            load_context(pid);
        }

    }

    /**
     * @brief Saves the context of the preempted process and loads the context
     * of the scheduled process.
     * @param preempted_pid The id of the preempted process.
     * @param scheduled_pid The id of the scheduled process.
     */
    void handle_preemption(int preempted_pid, int scheduled_pid) {

        // Saves the context of the process that was running.
        save_context(preempted_pid);

        // Loads the context of the process that is scheduled to run. If the
        // process is new, its context will be empty.
        load_context(scheduled_pid);
    }

private:
    Memory memory;
    std::vector<unsigned int> registers;
    unsigned int sp; // Stack Pointer
    unsigned int pc; // Program Counter
    unsigned int st; // Status

    // Loads the context of a process from memory.
    void load_context(int pid) {
        Context context = memory.load_context(pid);
        registers = context.get_registers();
        sp = context.get_sp();
        pc = context.get_pc();
        st = context.get_st();
    }

    // Saves the context of the current process in memory.
    void save_context(int pid) {
        Context context(registers, sp, pc, st);
        memory.save_context(pid, context);
    }

};

#endif // CPU_H