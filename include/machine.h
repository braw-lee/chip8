#ifndef MACHINE_H
#define MACHINE_H

#include "cpu.h"
#include "keyboard.h"
#include "eventHandler.h"

class Machine
{
public:
	void run(std::string& romPath);
};

#endif
