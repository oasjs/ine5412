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

        if (scheduler_type) {
            kernel.start_scheduler(scheduler_type);

        } else {
            std::cout << "Scheduler type: " << scheduler_type << std::endl;
            for (int i = 1; i <= 5; i++)
                kernel.start_scheduler(i);
        }
    }

private:
    File file;
	Kernel kernel;
};


#endif // SYSTEM_H