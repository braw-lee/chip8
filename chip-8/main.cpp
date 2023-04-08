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
		uint64_t deltaTime{};
		while(!quit)
		{
			quit = ehandler.handleEvents();

			uint64_t start_time = SDL_GetPerformanceCounter();
			for(int i=0; i< 700 / 60; i++)
			{
				cpu.runCycle();
			}
			cpu.updateDisplay();
			cpu.decrementTimers();

			uint64_t end_time = SDL_GetPerformanceCounter();
			deltaTime = (double)((end_time - start_time) * 1000) / SDL_GetPerformanceFrequency();
			SDL_Delay(16.67 > deltaTime ? 16.67 - deltaTime : 0);
		}
	}
	else
		std::cerr<<"\nError loading rom";

}
