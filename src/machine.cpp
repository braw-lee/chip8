#include "../include/machine.hpp"
#include "../include/config.hpp"

void Machine::run(std::string& romPath)
{
	Keyboard keyboard;
	EventHandler ehandler(keyboard.getKeys());
	Cpu cpu(keyboard.getKeys());
	if(cpu.loadRom(romPath))
	{
		bool quit{false};
		uint64_t deltaTime{};
		while(!quit)
		{
			quit = ehandler.handleEvents();

			//loop handleEvents() till user presses 'P' again
			if(configurations.gameState == GameState::PAUSED)
				continue;

			uint64_t start_time = SDL_GetPerformanceCounter();
			for(int i=0; i< configurations.instructionsPerSecond / configurations.framesPerSecond; i++)
			{
				cpu.runCycle();
			}
			cpu.updateDisplay();  //display at 60Hz
			cpu.decrementTimers();  //decrement timers at 60Hz

			uint64_t end_time = SDL_GetPerformanceCounter();
			deltaTime = (double)((end_time - start_time) * 1000) / SDL_GetPerformanceFrequency();
			SDL_Delay(16.67 > deltaTime ? 16.67 - deltaTime : 0);
		}
	}
	else
		std::cerr<<"\nError loading rom";
}
