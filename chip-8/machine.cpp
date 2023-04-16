#include "machine.h"

void Machine::run(std::string& romPath)
{
	Keyboard keyboard;
	EventHandler ehandler(keyboard.getKeys());
	Chip8 cpu(keyboard.getKeys());
	if(cpu.loadRom(romPath))
	{
		bool quit{false};
		uint64_t deltaTime{};
		while(!quit)
		{
			quit = ehandler.handleEvents();

			uint64_t start_time = SDL_GetPerformanceCounter();
			for(int i=0; i< 900 / 60; i++)
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
