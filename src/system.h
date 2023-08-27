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
	
private:	
	Kernel kernel;
	CPU cpu; //seconds
	Memory memory;
};

#endif // SYSTEM_H