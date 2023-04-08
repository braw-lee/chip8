#include "eventHandler.h"

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
			//return true when user presses 'esc' key
			if (_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				quit = true;

			if(_keyMapping.count(_event.key.keysym.scancode) != 0 )
				_keyState[_keyMapping[_event.key.keysym.scancode]] = Keyboard::KEY_DOWN;
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

