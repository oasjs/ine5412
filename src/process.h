#ifndef PROCESS_H
#define PROCESS_H

#include "../NamedType/include/named_type.hpp"

using pid = NamedType<int, struct pidTag>;
using startTime = NamedType<int, struct startTimeTag>;
using endTime = NamedType<int, struct endTimeTag>;
using duration = NamedType<int, struct durationTag>;
using staticPriority = NamedType<int, struct staticPriorityTag>;
using dynamicPriority = NamedType<int, struct dynamicPriorityTag>;
using state = NamedType<int, struct stateTag>;
using totalExecutionTime = NamedType<int, struct totalExecutionTimeTag>;
using quantumExecutionTime = NamedType<int, struct quantumExecutionTimeTag>;


/**
 * @class Process
 * @brief Represents each process and its contents.
 *
 */
class Process {
public:
    Process(pid p, startTime start, duration dur, staticPriority sPriority, dynamicPriority dPriority, state s)
        : pid(p), startTime(start), duration(dur), staticPriority(sPriority), dynamicPriority(dPriority), state(s) {
    }

    ~Process() {}

    void run() {
        totalExecutionTime++;
    }

    bool is_done() {
        return totalExecutionTime >= duration;
    }

    int getDuration() {
        return duration;
    }

    int getStaticPriority() {
        return staticPriority;
    }

protected:
    pid pid;
    startTime startTime;
    endTime endTime;
    duration duration;
    staticPriority staticPriority;
    dynamicPriority dynamicPriority;
    state state;
    totalExecutionTime totalExecutionTime;
    quantumExecutionTime quantumExecutionTime;
};

#endif // PROCESS_H