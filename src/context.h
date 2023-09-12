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
        registers = std::vector<unsigned int>(6);
        sp = 0;
        pc = 0;
        st = 0;
    }

    Context(std::vector<unsigned int> registers_,
            unsigned int sp_,
            unsigned int pc_,
            unsigned int st_) {
        registers = registers_;
        sp = sp_;
        pc = pc_;
        st = st_;
    }

    ~Context() {}

    std::vector<unsigned int> get_registers() {
        return registers;
    }

    unsigned int get_sp()  {
        return sp;
    }

    unsigned int get_pc() {
        return pc;
    }

    unsigned int get_st() {
        return st;
    }

private:
    std::vector<unsigned int> registers;
    unsigned int sp; // Stack Pointer
    unsigned int pc; // Program Counter
    unsigned int st; // Status
};

#endif // CONTEXT_H