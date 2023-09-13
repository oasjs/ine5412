#ifndef SYSTEM_H
#define SYSTEM_H

#include "kernel.h"
#include <vector>

/**
 * @class System
 * @brief Represents the Operating System.
 *
 */
class System
{
public:
	System(char* file_name) : kernel(), file(file_name) {}

	~System() {}

    /**
     * @brief Starts the system. It reads the file and starts the kernel.
     */
    void start(unsigned int scheduler_type) {
        file.read_file();
        if (scheduler_type)
            kernel.start(scheduler_type, file.get_processes_params());
        else
            for (int i = FCFS; i <= RR; i++)
                kernel.start(i, file.get_processes_params());
    }

private:
	Kernel kernel;
    File file;
};


#endif // SYSTEM_H