#ifndef SYSTEM_H
#define SYSTEM_H

#include "Kernel.h"
#include "CPU.h"
#include "Memory.h"

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