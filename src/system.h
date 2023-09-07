#ifndef SYSTEM_H
#define SYSTEM_H

#include "kernel.h"
#include <vector>

/**
 * @class System
 * @brief Represents the System and its contents.
 *
 */
class System
{
public:
	System(char* file_name) : file(file_name), kernel() {}

	~System() {}

    void start(int scheduler_type) {
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