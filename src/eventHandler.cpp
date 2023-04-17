#include "../include/eventHandler.h"
#include "../include/config.h"

#include <iostream> //temp

EventHandler::EventHandler(std::array<Keyboard::KeyState, 16>& keyState)
	:_keyState{keyState}
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
					configurations.gameState = RUNNING;
				else //configurations.gameState == GameState::RUNNING
				     	configurations.gameState = PAUSED;
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
