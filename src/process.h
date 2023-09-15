#ifndef PROCESS_H
#define PROCESS_H

#include <climits>

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
    Process() : pid(0),
                duration(0),
                priority(0),
                creation_time(0),
                total_execution_time(0),
                state(0),
                start(ULONG_MAX),
                end(0),
                waiting_time(0),
                context_changes(0) {}

    Process(unsigned long pid_,
            unsigned long duration_,
            unsigned long priority_,
            unsigned long creation_time_) : pid(pid_),
                                            duration(duration_),
                                            priority(priority_),
                                            creation_time(creation_time_),
                                            total_execution_time(0),
                                            state(0),
                                            start(ULONG_MAX),
                                            end(0),
                                            waiting_time(0),
                                            context_changes(0) {}

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
    void set_state(unsigned long state_, unsigned long current_time) {
        switch (state_)
        {
        case READY:
            state = READY;
            last_interrupt = current_time;
            break;
        case RUNNING:
            if (state == READY) {
                waiting_time += current_time - last_interrupt;
                context_changes++;
            }
            state = RUNNING;
            start = current_time > start ? start : current_time;
            break;
        case DONE:
            state = DONE;
            end = current_time;
            break;
        default:
            break;
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

    /**
     * @brief Returns the start time of the process.
     */
    unsigned long get_start() const {
        return start;}

    /**
     * @brief Returns the end time of the process.
     */
    unsigned long get_end() const {
        return end;}

    /**
     * @brief Returns the waiting time of the process.
     */
    unsigned long get_waiting_time() const {
        return waiting_time;}

    /**
     * @brief Returns the turnaround time of the process.
     */
    unsigned long get_turnaround_time() const {
        return end - creation_time;}

    /** 
     * @brief Returns the number of context changes of the process.
     */
    unsigned long get_context_changes() const {
        return context_changes;}


protected:
    unsigned long   pid;
    unsigned long   duration;
    unsigned long   priority;
    unsigned long   creation_time;
    unsigned long   total_execution_time;
    unsigned long   state;
    unsigned long   start;
    unsigned long   end;
    unsigned long   waiting_time;
    unsigned long   last_interrupt;
    unsigned long   context_changes;
};

#endif // PROCESS_H