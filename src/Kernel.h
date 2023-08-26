#ifndef KERNEL_H
#define KERNEL_H

#include <list>
#include "Scheduler.h"
#include "CPU.h"
#include "ReadFile.h"

/**
 * @class Kernel
 * @brief Represents each Kernel and its contents.
 *
 */
class Kernel {
public:
    Kernel() {}

    ~Kernel() {}

    void start() {}

private:
    Scheduler scheduler;
    CPU cpu;

    std::list<Process> readFile(int fileAdress) {
        File f;
        f.read_file();
        // Transform File type in std::list<Process>
        return f;
    }

};

#endif // KERNEL_H