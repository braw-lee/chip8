#ifndef CHIP8_H
#define CHIP8_H

#include "display.h"
#include "eventHandler.h"
#include "keyboard.h"
#include "randomNumber.h"
#include "utility.h"

#include <array>
#include <cstdint>
#include <string>

const int MEMORY_SIZE = 4096;  //Chip-8 has direct access to upto 4kb of RAM
const int MEMORY_START = 0x200;  //we should start reading from 0x200

#define DEBUG true

class Chip8
{
public:
	Chip8(std::array<Keyboard::KeyState, 16>& keyState);  //default constructor
	bool loadRom(std::string& path);
	uint16_t fetch();
	void runCycle();
	void decodeAndExecute(uint16_t opcode);
	void panicQuit(uint16_t opcode);
	void decrementTimers();
	void updateDisplay();
private:
	std::array<uint8_t, MEMORY_SIZE> _memory;  //memory
	const std::array<uint8_t, 80> _font;
	uint16_t _pc;  //program counter
	uint16_t _i; //index register
	std::array<uint16_t, 16> _stack;  //used to call functions and return from them
	uint8_t _sp;  //stack pointer
	uint8_t _delayTimer;
	uint8_t _soundTimer;
	std::array<uint8_t, 16> _v;  //16 8-bit registers

	Display _display;
	bool _updateDisplay;
	
	std::array<Keyboard::KeyState, 16>& _keyState;
};

#endif
