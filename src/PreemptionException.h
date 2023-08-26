#ifndef PREEMPRION_EXCEPTION_H
#define PREEMPRION_EXCEPTION_H

#include <stdexcept>
#include <string>

/**
 * @class PreemptionException
 * @brief Custom exception to treat the preemptions.
 *
 * This exception will be thrown when a process is
 * preempted
 *
 */
class PreemptionException : public std::exception {
public:
    PreemptionException(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string msg;
    int blockedPid;
    int startingPid;
};

#endif // PREEMPRION_EXCEPTION_H