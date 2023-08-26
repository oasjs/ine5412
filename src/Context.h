#ifndef CONTEXT_H
#define CONTEXT_H

#include <list>

/**
 * @class Context
 * @brief Represents the Context and its contents.
 *
 */
class Context {
public:
    Context() {}

    ~Context() {}

private:
    std::list<int> registers;
    int sp; // Stack Pointer
    int pc; // Program Counter
};

#endif // CONTEXT_H