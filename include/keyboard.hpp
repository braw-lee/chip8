#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <array>

class Keyboard
{
public:
	enum KeyState
	{
		KEY_UP,  //key not pressed
		KEY_DOWN //key pressed
	};
	
	//initializes all keys to KEY_UP
	Keyboard();

	//returns reference to std::array of keys
	std::array<KeyState, 16>& getKeys();
private:
	std::array<KeyState, 16> _keyState;
};

#endif
