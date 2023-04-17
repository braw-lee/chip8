#ifndef MACHINE_HPP
#define MACHINE_HPP

#include "cpu.hpp"
#include "keyboard.hpp"
#include "eventHandler.hpp"

class Machine
{
public:
	void run(std::string& romPath);
};

#endif
