#include "system.h"

int main(int argc , char** argv) {

    if (argc < 2) {
        std::cout << "Usage: ./scheduler <input_file> scheduler_type (optional)" << std::endl;
        return 1;
    }

    // As the second argument is optional, if it is not passed, the scheduler
    // type is set to 0, which means that all schedulers will be run.
    int scheduler_type = 0;
    if (argc == 3)
        scheduler_type = atoi(argv[2]);

    System system = System(argv[1]);
    system.start(scheduler_type);
    return 0;
}
