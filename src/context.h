#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>

/**
 * @class Context
 * @brief Represents the context of a process. It contains the registers, the
 * stack pointer, the program counter and the status.
 *
 */
class Context {
public:

    Context() {
        registers = std::vector<unsigned long>(6);
        sp = 0;
        pc = 0;
        st = 0;
    }

    Context(std::vector<unsigned long> registers_,
            unsigned long sp_,
            unsigned long pc_,
            unsigned long st_) {
        registers = registers_;
        sp = sp_;
        pc = pc_;
        st = st_;
    }

    ~Context() {}

    std::vector<unsigned long> get_registers() {
        return registers;
    }

    unsigned long get_sp()  {
        return sp;
    }

    unsigned long get_pc() {
        return pc;
    }

    unsigned long get_st() {
        return st;
    }

private:
    std::vector<unsigned long> registers;
    unsigned long sp; // Stack Pointer
    unsigned long pc; // Program Counter
    unsigned long st; // Status
};

#endif // CONTEXT_H