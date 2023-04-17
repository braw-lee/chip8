#include "../include/cpu.hpp"
#include "../include/display.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace Utility;

Cpu::Cpu(std::array<Keyboard::KeyState, 16>& keyState)
	: _font
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        	0x20, 0x60, 0x20, 0x20, 0x70, // 1
        	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	},
	_pc{MEMORY_START},
	_i{},
	_sp{},
	_delayTimer{},
	_soundTimer{},
	_updateDisplay{false},
	_keyState{keyState}
{
	//setup fonts in memory
	for(int i=0; i<80; i++)
		_memory[i] = _font[i];

	std::cout<<"\nCpu constructor!";
}

bool Cpu::loadRom(std::string& path)
{
	std::ifstream file(path, std::ios::binary|std::ios::in);

	if(!file.is_open())
		return false;

	uint8_t byte;
	uint16_t memoryIterator = MEMORY_START;

	while(!file.eof())
	{
		byte = file.get();  //reading a byte from file
		_memory[memoryIterator] = byte;  //writing the read byte into memory
		memoryIterator++;
	}

	#if DEBUG
	std::cout<<"\nRom loaded into memory";
	#endif
	return true;
}

uint16_t Cpu::fetch()
{
	uint16_t opcodeFirstHalf = _memory[_pc]<<8;
	uint16_t opocodeSecondHalf = _memory[_pc+1];
	uint16_t opcode = opcodeFirstHalf | opocodeSecondHalf;
	_pc +=2;
	return opcode;
}

void Cpu::runCycle()
{
	uint16_t opcode = fetch();

	#if DEBUG
	std::cout<<"\n\nRunning cycle for opcode : "<<toHex(opcode, 4);
	#endif

	decodeAndExecute(opcode);
	
}

void Cpu::panicQuit(uint16_t opcode)
{
	std::cout<<"\nCannot recognize instruction : "<<toHex(opcode, 4);
	exit(1);
}

void Cpu::decrementTimers()
{
	if(_delayTimer > 0)
		_delayTimer--;
	if(_soundTimer > 0)
	{
		_soundTimer--;
		speaker.unpause();
	}
	else
		speaker.pause();
}

void Cpu::updateDisplay()
{
	if(_updateDisplay)
	{
		std::cout<<"\nDisplaying screen";
		_display.updateScreen();
		_updateDisplay = false;
	}
}
