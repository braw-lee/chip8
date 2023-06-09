#include "../include/eventHandler.hpp"
#include "../include/config.hpp"
#include "../include/randomNumber.hpp"

EventHandler::EventHandler(std::array<Keyboard::KeyState, 16>& keyState, Display& display)
	:_keyState{keyState}, _display{display}
{}

bool EventHandler::handleEvents()
{
	bool quit{false};
	//SDL_PollEvent returns 0 when event queue is empty
	while(SDL_PollEvent(&_event) != 0)
	{
		//return true when user tries to quit the program
		if(_event.type == SDL_QUIT)
			quit = true;

		//handles events when user presses a key
		if(_event.type == SDL_KEYDOWN)
		{
			if(_keyMapping.count(_event.key.keysym.scancode) != 0 )
				_keyState[_keyMapping[_event.key.keysym.scancode]] = Keyboard::KEY_DOWN;
		
			//return true when user presses 'esc' key
			if (_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				quit = true;
			//pause or unpause game when user presses 'P'
			if (_event.key.keysym.scancode == SDL_SCANCODE_P)
			{
				if (configurations.gameState == GameState::PAUSED)
				{
					configurations.gameState = RUNNING;
					_display.updateWindowName("CHIP-8");
				}
				else //configurations.gameState == GameState::RUNNING
				{
					configurations.gameState = PAUSED;
					_display.updateWindowName("CHIP-8 : PAUSED");
				}
			}
			//change colorCombo when user presses 'L'
			if(_event.key.keysym.scancode == SDL_SCANCODE_L)
			{
				configurations.currentCombo = colorComboList[RandomNumber::generateRandomNumber(0,colorComboList.size()-1)];
			}
		}

		//handles events when user releases a key
		if(_event.type == SDL_KEYUP)
		{
			if(_keyMapping.count(_event.key.keysym.scancode) != 0)
				_keyState[_keyMapping[_event.key.keysym.scancode]] = Keyboard::KEY_UP;
		}
	}

	return quit;
}
