#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>

const int MEMORY_SIZE = 4096;  //Chip-8 has direct access to upto 4kb of RAM

class Chip8
{
public:
	Chip8();  //default constructor
	void decode(uint16_t opcode);	
private:
	uint8_t _memory[MEMORY_SIZE];  //memory
	uint8_t _pc;  //program counter
	uint16_t _i; //index register
	uint16_t _stack[16];  //used to call functions and return from them
	uint8_t _sp;  //stack pointer
	uint8_t _delayTimer;
	uint8_t _soundTimer;
	uint8_t _v[16];  //16 8-bit registers
	const uint8_t _font[80];
	
};

#endif
