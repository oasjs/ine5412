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
	System(char* file_name) : file(file_name) {
        file.read_file();
        kernel = Kernel(file.get_processes_params());
    }

	~System() {}

    /**
     * @brief Starts the system. It reads the file and starts the kernel.
     */
    void start(unsigned int scheduler_type) {

        std::string scheduling_types[] = {"First Come First Served",
                                         "Shortest Job First",
                                         "Priority, no preemption",
                                         "Prioity, with preemption",
                                         "Round Robin"};

        if (scheduler_type) {
            kernel.start_scheduler(scheduler_type);

        } else {
            for (int i = 1; i <= 5; i++) {
                std::cout << "Scheduler type: " << scheduling_types[i-1]
                                                << std::endl << std::endl;
                kernel.start_scheduler(i);
                std::cout << std::endl;
            }
        }
    }

private:
    File file;
	Kernel kernel;
};


#endif // SYSTEM_H