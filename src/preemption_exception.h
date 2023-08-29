#ifndef PREEMPRION_EXCEPTION_H
#define PREEMPRION_EXCEPTION_H

#include <stdexcept>
#include <string>

/**
 * @class PreemptionException
 * @brief Custom exception to treat the preemptions.
 *
 * This exception will be thrown when a process is
 * preempted.
 *
 */
class PreemptionException : public std::exception {
public:
    PreemptionException(const int scheduled_pid) noexcept;
    const char* what() const noexcept override;

    int get_preempted_pid() const noexcept {
        return preempted_pid;
    }

    int get_scheduled_pid() const noexcept {
        return scheduled_pid;
    }

private:
    int preempted_pid;
    int scheduled_pid;
};

#endif // PREEMPRION_EXCEPTION_H