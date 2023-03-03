#include "chip8.h"
#include <iostream>

//used for debugging
#define DEBUG true

Chip8::Chip8()
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
	}
{
	std::cout<<"\nChip8 constructor!";
}

void Chip8::decode(uint16_t opcode)
{
	uint8_t x = (opcode & 0x0F00)>>8;  //second nibble
	uint8_t y = (opcode & 0x00F0)>>4;  //third nibble
	uint8_t n = (opcode & 0x000F);     //fourth nibble
	uint8_t nn = (opcode & 0x00FF);    //third and fourth nibble
	uint16_t nnn = (opcode & 0x0FFF);  //second, third and fourth nibble
	
	#if DEBUG
	std::cout<<"\nopcode : "<<std::hex<<int(opcode);
	std::cout<<"\nx : "<<std::hex<<int(x);
	std::cout<<"\ny : "<<std::hex<<int(y);
	std::cout<<"\nn : "<<std::hex<<int(n);
	std::cout<<"\nnn : "<<std::hex<<int(nn);
	std::cout<<"\nnnn : "<<std::hex<<int(nnn);
	#endif

	//test first nibble
	switch(opcode>>12)
	{
		//instructions with first nibble as 0x0
		case(0x0):
		{
			switch(nn)
			{
				case(0xE0):
				{
					//clear screen
				}
				case(0xEE):
				{
					_pc = _stack[_sp];
					_sp--;

					break;
				}
			}

			break;
		}
		
		case(0x1):
		{
			_pc = nnn;

			break;
		}

		case(0x2):
		{
			_sp++;
			_stack[_sp] = _pc;
			_pc = nnn;

			break;
		}

		case(0x3):
		{
			if(_v[x] == nn)
				_pc += 2;

			break;
		}

		case(0x4):
		{
			if(_v[x] != nn)
				_pc += 2;

			break;
		}

		case(0x5):
		{
			if(_v[x] == _v[y])
				_pc += 2;

			break;
		}

		case(0x6):
		{
			_v[x] = nn;

			break;
		}

		case(0x7):
		{
			_v[x] = _v[x]+nn;

			break;
		}

		case(0x8):
		{
			_v[x] = _v[y];

			break;
		}

		case(0x9):
		{
			//todo
		}

		case(0xA):
		{
			_i = nnn;

			break;
		}

		case(0xD):
		{}

		default: 
			std::cerr<<"\nCannot recognize instruction : "<<std::hex<<int(opcode);
			 exit(1);
	}
}
