#ifndef MEMORY_H
#define MEMORY_H

#include <list>


/**
 * @class Memory
 * @brief Represents the Memory and its contents.
 *
 */
class Memory {
public:
    Memory() {}

    ~Memory() {}

    void saveContext() {}

    void loadContext() {}

private:
    std::list<int> contextMap;  // Check the type of the list

};

#endif // MEMORY_H