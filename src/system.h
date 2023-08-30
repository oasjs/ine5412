#ifndef SYSTEM_H
#define SYSTEM_H

#include "kernel.h"
#include "read_file.h"

/**
 * @class System
 * @brief Represents the System and its contents.
 *
 */
class System
{
public:
	System(char* file_name_) {
        File f(file_name_);
        f.read_file();
        kernel = Kernel(f.get_processes_params());
    }

	~System() {}

    void start(int scheduler_type) {
        if (scheduler_type)
            kernel.start(scheduler_type);
        else
            for (int i = FCFS; i <= RR; i++)
                kernel.start(i);
    }
	
private:	
	Kernel kernel;
};


enum SchedulerType {
    FCFS = 1,
    SJF,
    PNP,
    PP,
    RR
};

#endif // SYSTEM_H