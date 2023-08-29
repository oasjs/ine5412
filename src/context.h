#ifndef CONTEXT_H
#define CONTEXT_H

#include <list>

/**
 * @class Context
 * @brief Represents the Context and its contents.
 *
 */
class Context {
public:

    Context() {
        registers = vector<int>(6);
        sp = 0;
        pc = 0;
        st = 0;
    }

    Context(vector<int> registers_, int sp_, int pc_, int st_) {
        registers = registers_;
        sp = sp_;
        pc = pc_;
        st = st_;
    }

    ~Context() {}

    vector<int> get_registers() {
        return registers;
    }

    int get_sp()  {
        return sp;
    }

    int get_pc() {
        return pc;
    }

    int get_st() {
        return st;
    }

private:
    vector<int> registers;
    int sp; // Stack Pointer
    int pc; // Program Counter
    int st; // Status
};

#endif // CONTEXT_H