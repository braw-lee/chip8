#include "../include/keyboard.hpp"

Keyboard::Keyboard()
{
	_keyState.fill(KEY_UP);
}

std::array<Keyboard::KeyState, 16>& Keyboard::getKeys()
{
	return _keyState;
}
