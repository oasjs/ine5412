#ifndef MEMORY_H
#define MEMORY_H

#include <unordered_map>

/**
 * @class Memory
 * @brief Represents the Memory and its contents.
 *
 */
class Memory {
public:
    Memory() {}

    ~Memory() {}

    /**
     * @brief Saves the context of a process.
     */
    void save_context(int pid, Context context) {
        contextMap[pid] = context;
    }

    /**
     * @brief Loads the context of a process. If the process has no context
     * saved, returns an empty context.
     */
    Context load_context(int pid) {
        if (contextMap.find(pid) != contextMap.end())
            return contextMap[pid];
        else
            return Context();
    }

private:
    std::unordered_map<int, Context> contextMap;
};

#endif // MEMORY_H