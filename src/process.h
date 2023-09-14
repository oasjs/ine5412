#ifndef PROCESS_H
#define PROCESS_H

enum States {
    NEW,
    READY,
    RUNNING,
    DONE
};

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
        state = 0;
    }

    Process(unsigned long pid_, unsigned long duration_, unsigned long priority_) {
        pid = pid_;
        duration = duration_;
        priority = priority_;
        total_execution_time = 0;
        state = 0;
    }

    ~Process() {}

    /**
     * @brief Increments the total execution time of the process.
    */
    void run() {
        total_execution_time++;
    }

    /**
     * @return True if the process has finished its execution. Otherwise
     * returns false.
     */
    bool is_done() {
        return total_execution_time >= duration;
    }

    /**
     * @brief Sets the state of the process.
     * 
     * @param s The state of the process, being 1 for READY, 2 for RUNNING and
     * 3 for DONE.
     */
    void set_state(unsigned long s) {
        if (s == READY || s == RUNNING || s == DONE) {
            state = s;
        }
    }

    /**
     * @return The state mneumonic of the process.
     */
    std::string get_state() {
        switch (state)
        {
        case READY:
            return "--";
            break;
        case RUNNING:
            return "##";
            break;
        case
            DONE:
            return "  ";
            break;
        default:
            return "  ";
            break;
        }
    }

    /**
     * @brief Returns the process ID.
     */
    unsigned long get_pid() const {
        return pid;}

    /**
     * @brief Returns the maximum duration of the process. If the duration is
     *  0, the process is invalid.
     */
    unsigned long get_duration() const {
        return duration;}

    /**
     * @brief Returns the priority of the process. This priority is always
     * static.
     */
    unsigned long get_priority() const {
        return priority;}

    /**
     * @brief Returns the total execution time of the process.
     */
    unsigned long get_total_execution_time() const {
        return total_execution_time;}

protected:
    unsigned long    pid;
    unsigned long    duration;
    unsigned long    priority;
    unsigned long    total_execution_time;
    unsigned long    state;
};

#endif // PROCESS_H