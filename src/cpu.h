#ifndef CPU_H
#define CPU_H

#include <list>
#include "memory.h"

/**
 * @class CPU
 * @brief Represents the CPU and its contents.
 *
 */
class CPU {
public:
    CPU() {}

    ~CPU() {}

    void handlePreemption() {}

private:
    Memory memory;
    std::list<int> registers;   // Check the type of the list
    int sp; // Stack Pointer
    int pc; // Program Counter
    int st; // Status

    void generateContext() {}

    void loadContext() {}

    void saveContext() {}

};

#endif // CPU_H