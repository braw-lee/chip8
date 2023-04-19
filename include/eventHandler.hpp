#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

/*
 *mapping of COSMAC vip keypad to left side of QWERTY keyboard
 *
 * 1 2 3 C          1 2 3 4
 * 4 5 6 D   --->   Q W E R
 * 7 8 9 E   --->   A S D F
 * A 0 B F          Z X C V
*/

#include <array>
#include <cstdint>
#include <SDL2/SDL.h>
#include <map>

#include "keyboard.hpp"

class EventHandler
{
public:
	EventHandler(std::array<Keyboard::KeyState, 16>& keyState);

	//returns true if user signals to quit program
	//else returns false
	bool handleEvents();

private:
	//SDL_Event is a union containing structures
	//for all types of SDL events
	SDL_Event _event;

	//map QWERTY keypad to COSMAC VIP keypad
	std::map<SDL_Scancode, uint8_t> _keyMapping
	{
		{SDL_SCANCODE_1, 0x1},
		{SDL_SCANCODE_2, 0x2},
		{SDL_SCANCODE_3, 0x3},
		{SDL_SCANCODE_4, 0xC},
		{SDL_SCANCODE_Q, 0x4},
		{SDL_SCANCODE_W, 0x5},
		{SDL_SCANCODE_E, 0x6},
		{SDL_SCANCODE_R, 0xD},
		{SDL_SCANCODE_A, 0x7},
		{SDL_SCANCODE_S, 0x8},
		{SDL_SCANCODE_D, 0x9},
		{SDL_SCANCODE_F, 0xE},
		{SDL_SCANCODE_Z, 0xA},
		{SDL_SCANCODE_X, 0x0},
		{SDL_SCANCODE_C, 0xB},
		{SDL_SCANCODE_V, 0xF}
	};

	std::array<Keyboard::KeyState,16>& _keyState;
};

#endif
