
#ifndef PROCESS_H
#define PROCESS_H

/**
 * @class Process
 * @brief Represents each process and its contents.
 *
 */
class Process {
public:
    Process() {}

    ~Process() {}

protected:
    int pid;
    int startTime;
    int endTime;
    int duration;
    int staticPriority;
    int dynamicPriority;
    int state;
    int totalExecutionTime;
    int quantumExecutionTime;
};

#endif // PROCESS_H