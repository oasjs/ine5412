#ifndef SYSTEM_H
#define SYSTEM_H

#include "kernel.h"
#include "cpu.h"
#include "memory.h"

/**
 * @class System
 * @brief Represents the System and its contents.
 *
 */
class System
{
public:
	System() {}

	~System() {}

    void start() {
        kernel.start();
    }
	
private:	
	Kernel kernel;
};

#endif // SYSTEM_H