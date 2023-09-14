#include "system.h"

int main(int argc , char** argv) {

    if (argc < 2) {
        std::cout << "Usage: ./scheduler <input_file> scheduler_type (optional) quantum (optional)" << std::endl;
        return 1;
    }

    // As the second argument is optional, if it is not passed, the scheduler
    // type is set to 0, which means that all schedulers will be run.
    unsigned int scheduler_type = 0;
    if (argc == 3)
        scheduler_type = atoi(argv[2]);

    // The third argument is also optional, if it is not passed, the quantum
    // is set to 2.
    unsigned int quantum = 2;
    if (argc == 4)
        quantum = atoi(argv[3]);

    System system = System(argv[1]);
    system.start(scheduler_type, quantum);
    return 0;
}
