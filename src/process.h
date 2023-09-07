#ifndef PROCESS_H
#define PROCESS_H

/**
 * @class Process
 * @brief Represents a process in the system.
 *
 */
class Process {
public:
    Process() {
        pid = 0;
        duration = 0;
        priority = 0;
        total_execution_time = 0;
    }

    Process(unsigned int pid_, unsigned int duration_, unsigned int priority_) {
        pid = pid_;
        duration = duration_;
        priority = priority_;
        total_execution_time = 0;
    }

    ~Process() {}

    /**
     * @brief Increments the total execution time of the process and returns
     *  true if the process has finished its execution. Otherwise returns false.
    */
    void run() {
        total_execution_time++;}

    bool is_done() {
        return total_execution_time >= duration;}

    /**
     * @brief Returns the process ID.
     */
    unsigned int get_pid() const {
        return pid;}

    /**
     * @brief Returns the maximum duration of the process. If the duration is
     *  0, the process is invalid.
     */
    unsigned int get_duration() const {
        return duration;}

    /**
     * @brief Returns the priority of the process. This priority is always
     * static.
     */
    unsigned int get_priority() const {
        return priority;}

protected:
    unsigned int    pid;
    unsigned int    duration;
    unsigned int    priority;
    unsigned int    total_execution_time;
};

#endif // PROCESS_H