#ifndef MACHINE_H
#define MACHINE_H

#include "chip8.h"
#include "keyboard.h"
#include "eventHandler.h"

class Machine
{
public:
	void run(std::string& romPath);
};

#endif
