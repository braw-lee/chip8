#ifndef MACHINE_HPP
#define MACHINE_HPP

#include "cpu.hpp"
#include "keyboard.hpp"
#include "eventHandler.hpp"

class Machine
{
public:
	//main loop; handle events, run cpu cycles, decrement timers at a given rate
	void run(std::string& romPath);
};

#endif
