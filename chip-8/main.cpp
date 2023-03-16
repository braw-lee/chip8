#include "chip8.h"

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
	Chip8 a;

	if(a.loadRom(path))
	{
		while(!a.quitGameLoop())
		{
			a.runCycle();
//			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
	else
		std::cerr<<"\nError loading rom";

}
