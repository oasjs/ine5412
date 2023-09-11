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
        registers = std::vector<int>(6);
        sp = 0;
        pc = 0;
        st = 0;
    }

    ~CPU() {}

    // Simulates the CPU changing states as it executes a process.
    void change_state() {
        // Prepares to generate a random number.
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 100);

        // Sets each information of the cpu state to a random number.
        for (int n = 0; n < 6; ++n) {
            registers[n] = dis(gen);
        }
        int sp = dis(gen);
        int pc = dis(gen);
        int st = dis(gen);
    }

    // Handles the preemption of a process.
    void handle_preemption(int preempted_pid, int scheduled_pid) {

        // Saves the context of the process that was running.
        save_context(preempted_pid);

        // Loads the context of the process that is scheduled to run. If the
        // process is new, its context will be empty.
        load_context(scheduled_pid);
    }

private:
    Memory memory;
    std::vector<int> registers;
    int sp; // Stack Pointer
    int pc; // Program Counter
    int st; // Status

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