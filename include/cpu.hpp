#ifndef CPU_HPP
#define CPU_HPP

#include "display.hpp"
#include "eventHandler.hpp"
#include "keyboard.hpp"
#include "randomNumber.hpp"
#include "utility.hpp"
#include "sound.hpp"

#include <array>
#include <cstdint>
#include <string>

const int MEMORY_SIZE = 4096;  //Chip-8 has direct access to upto 4kb of RAM
const int MEMORY_START = 0x200;  //we should start reading from 0x200

#define DEBUG true

class Cpu
{
public:
	Cpu(std::array<Keyboard::KeyState, 16>& keyState, Display& display);
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
	uint8_t _delayTimer;  //decremented at 60Hz
	uint8_t _soundTimer;  //decremented at 60Hz, play sound when _soundTimer != 0
	std::array<uint8_t, 16> _v;  //16 8-bit registers

	Display& _display;
	bool _updateDisplay;
	
	std::array<Keyboard::KeyState, 16>& _keyState;

	Sound speaker;
};

#endif
