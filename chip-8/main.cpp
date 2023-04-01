#include "chip8.h"
#include "keyboard.h"
#include "eventHandler.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout<<"\nUsage : ./a <romName.ch8>";
		return 1;
	}
	std::string path = argv[1];

	Keyboard keyboard;
	Chip8 cpu(keyboard.getKeys());
	EventHandler ehandler(keyboard.getKeys());
	if(cpu.loadRom(path))
	{
		bool quit{false};
		while(!quit)
		{
			quit = ehandler.handleEvents();
			cpu.runCycle();
		}
//			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	else
		std::cerr<<"\nError loading rom";

}
