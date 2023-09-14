#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>


/**
 * @file input_generator.cpp
 * @brief Generates input files for the scheduler.
 * 
 * This file generates input files for the scheduler. The input files are
 * generated according to the following parameters: number of processes,
 * maximum duration of the processes and priority of the processes. The
 * parameters are generated randomly, according to the limits defined in the
 * input arguments.
 * 
 * @param number_of_processes The number of processes to be generated.
 */
int main(int argc, char** argv) {
    if (argc < 5) {
        std::cout << "Usage: ./input_generator <number_of_processes> <max_creation_time> <max_duration> <max_priority>" << std::endl;
        return 1;
    }

    unsigned int number_of_processes = atoi(argv[1]);
    unsigned int max_creation_time = atoi(argv[2]);
    unsigned int max_duration = atoi(argv[3]);
    unsigned int max_priority = atoi(argv[4]);

    std::ofstream file;
    file.open("input.txt");

    srand(time(NULL));

    file    << rand() % max_creation_time << " "
            << rand() % max_duration +1 << " "
            << rand() % max_priority;
    for (int i = 1; i < number_of_processes; i++) {
        file    << std::endl
                << rand() % max_creation_time << " "
                << rand() % max_duration + 1 << " "
                << rand() % max_priority;
    }

    file.close();

    return 0;
}