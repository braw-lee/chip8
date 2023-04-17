#include "../include/machine.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout<<"\nUsage : ./a <romName.ch8>";
		return 1;
	}
	std::string romPath = argv[1];

	Machine chip8_machine;
	chip8_machine.run(romPath);
}
