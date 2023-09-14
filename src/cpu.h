#ifndef CPU_H
#define CPU_H

#include <iostream>
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
        registers = std::vector<unsigned long>(6);
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
    void process(unsigned long pid) {

        // If the process is new to the processor, try to load its context.
        if (pid != registers[0]) {
            load_context(pid);
            registers[0] = pid;
        }

        #ifdef DEBUG
        std::cout   << "CPU State: " << std::endl;
        std::cout   << "PID: " << registers[0] << std::endl;
        std::cout   << "R1: " << registers[1] << "  "
                    << "R2: " << registers[2] << "  "
                    << "R3: " << registers[3] << "  "
                    << "R4: " << registers[4] << "  "
                    << "R5: " << registers[5] << std::endl;
        std::cout   << "SP: " << sp << "  " 
                    << "PC: " << pc << "  " 
                    << "ST: " << st << std::endl;
        std::cout   << std::endl;
        #endif

        // Simulates the process running for one second.
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
    }

    /**
     * @brief Saves the context of the preempted process and loads the context
     * of the scheduled process.
     * @param preempted_pid The id of the preempted process.
     * @param scheduled_pid The id of the scheduled process.
     */
    void handle_preemption(unsigned long preempted_pid,
                            unsigned long scheduled_pid) {

        #ifdef DEBUG
        std::cout   << "** A preemption has occured!" << std::endl;
        std::cout   << "** Preempted PID: " << preempted_pid << std::endl;
        std::cout   << "** Context: " << std::endl;
        std::cout   << "** PID: " << registers[0] << std::endl;
        std::cout   << "** R1: " << registers[1] << "  "
                    << "R2: " << registers[2] << "  "
                    << "R3: " << registers[3] << "  "
                    << "R4: " << registers[4] << "  "
                    << "R5: " << registers[5] << std::endl;
        std::cout   << "** SP: " << sp << "  " 
                    << "PC: " << pc << "  " 
                    << "ST: " << st << std::endl;
        std::cout   << std::endl;
        #endif

        // Saves the context of the process that was running.
        save_context(preempted_pid);

        // Loads the context of the process that is scheduled to run. If the
        // process is new, its context will be empty.
        load_context(scheduled_pid);

        #ifdef DEBUG
        std::cout   << "** Scheduled PID: " << scheduled_pid << std::endl;
        std::cout   << "** Context: " << std::endl;
        std::cout   << "** PID: " << registers[0] << std::endl;
        std::cout   << "** R1: " << registers[1] << "  "
                    << "R2: " << registers[2] << "  "
                    << "R3: " << registers[3] << "  "
                    << "R4: " << registers[4] << "  "
                    << "R5: " << registers[5] << std::endl;
        std::cout   << "** SP: " << sp << "  " 
                    << "PC: " << pc << "  " 
                    << "ST: " << st << std::endl;
        std::cout   << std::endl;
        #endif
    }

private:
    Memory memory;
    std::vector<unsigned long> registers;
    unsigned long sp; // Stack Pointer
    unsigned long pc; // Program Counter
    unsigned long st; // Status

    // Loads the context of a process from memory.
    void load_context(unsigned long pid) {
        Context context = memory.load_context(pid);
        registers = context.get_registers();
        sp = context.get_sp();
        pc = context.get_pc();
        st = context.get_st();
    }

    // Saves the context of the current process in memory.
    void save_context(unsigned long pid) {
        Context context(registers, sp, pc, st);
        memory.save_context(pid, context);
    }

};

#endif // CPU_H