#include "chip8.h"
#include "display.h"

#include <cstdlib>
#include <fstream>
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
	},
	_pc{MEMORY_START},
	_i{},
	_sp{},
	_delayTimer{},
	_soundTimer{},
	_updateDisplay{false},
	_quitGameLoop{false}
{
	std::cout<<"\nChip8 constructor!";
}

bool Chip8::loadRom(std::string& path)
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

void Chip8::decodeAndExecute(uint16_t opcode)
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
				case(0xE0):  //CLS
				{
					_display.clear();
					_updateDisplay = true;

					#if DEBUG
					std::cout<<"\nCLS";
					#endif
					break;
				}
				case(0xEE):  //RET
				{
					_pc = _stack[_sp];
					_sp--;

					#if DEBUG
					std::cout<<"\nRET";
					std::cout<<"\n_pc : "<<std::hex<<(int)_pc;
					std::cout<<"\n_sp : "<<std::hex<<(int)_sp;
					#endif
					break;
				}
			}
			break;
		}
		
		case(0x1):  //JP addr
		{
			_pc = nnn;

			#if DEBUG
			std::cout<<"\nJP addr";
			std::cout<<"\n_pc : "<<std::hex<<(int)_pc;
			#endif
			break;
		}

		case(0x2):  //CALL addr
		{
			_sp++;
			_stack[_sp] = _pc;
			_pc = nnn;

			#if DEBUG
			std::cout<<"\nCALL addr";
			std::cout<<"\n_sp : "<<std::hex<<(int)_sp;
			std::cout<<"\n_stack[_sp] : "<<std::hex<<(int)_stack[_sp];
			std::cout<<"\n_pc : "<<std::hex<<(int)_pc;
			#endif
			break;
		}

		case(0x3):  //SE Vx, byte
		{
			if(_v[x] == nn)
				_pc += 2;

			#if DEBUG
			std::cout<<"\nSE Vx, byte";
			std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
			std::cout<<"\nnn : "<<std::hex<<(int)nn;
			std::cout<<"\n_pc : "<<std::hex<<(int)_pc;
			#endif
			break;
		}

		case(0x4):  //SNE Vx, byte
		{
			if(_v[x] != nn)
				_pc += 2;

			#if DEBUG
			std::cout<<"\nSNE Vx, byte";
			std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
			std::cout<<"\n_pc : "<<std::hex<<(int)_pc;
			#endif
			break;
		}

		case(0x5):  //SE Vx, Vy
		{
			if(_v[x] == _v[y])
				_pc += 2;

			#if DEBUG
			std::cout<<"\nSE Vx, Vy";
			std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
			std::cout<<"\nV["<<std::hex<<y<<"] : "<<(int)_v[y];
			std::cout<<"\n_pc : "<<(int)_pc;
			#endif
			break;
		}

		case(0x6):  //LD Vx, byte
		{
			_v[x] = nn;
			
			#if DEBUG
			std::cout<<"\nLD Vx, byte";
			std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
			#endif
			break;
		}

		case(0x7):  //ADD Vx, byte
		{
			_v[x] = _v[x]+nn;

			#if DEBUG
			std::cout<<"\nADD Vx, byte";
			std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
			#endif
			break;
		}

		case(0x8):
		{
			switch(n)
			{
				case(0x0):  //LD Vx, Vy
				{
					_v[x] = _v[y];

					#if DEBUG
					std::cout<<"\nLD Vx, Vy";
					std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
					std::cout<<"\nV["<<std::hex<<y<<"] : "<<(int)_v[y];
					#endif
					break;
				}

				case(0x1):  //OR Vx, Vy
				{
					_v[x] = _v[x] | _v[y];
					
					#if DEBUG
					std::cout<<"\nOR Vx, Vy";
					std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
					std::cout<<"\nV["<<std::hex<<y<<"] : "<<(int)_v[y];
					#endif
					break;
				}

				case(0x2):  //AND Vx, Vy
				{
					_v[x] = _v[x] & _v[y];

					#if DEBUG
					std::cout<<"\nAND Vx, Vy";
					std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
					std::cout<<"\nV["<<std::hex<<y<<"] : "<<(int)_v[y];
					#endif
					break;
				}

				case(0x3):  //XOR Vx, Vy
				{
					_v[x] = _v[x] ^ _v[y];

					#if DEBUG
					std::cout<<"\nXOR Vx, Vy";
					std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
					std::cout<<"\nV["<<std::hex<<y<<"] : "<<(int)_v[y];
					#endif
					break;
				}

				case(0x4):  //ADD Vx, Vy
				{
					if(_v[x] + _v[y] > 0xFF)
						_v[0xF] = 1;
					else
						_v[0xF] = 0;
					_v[x] = _v[x] + _v[y];

					#if DEBUG
					std::cout<<"\nADD Vx, Vy";
					std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
					std::cout<<"\nV["<<std::hex<<y<<"] : "<<(int)_v[y];
					std::cout<<"\nV[0xF] : "<<(int)_v[0xF];
					#endif
					break;
				}

				case(0x5):  //SUB Vx, Vy
				{
					if(_v[x] > _v[y])
						_v[0xF] = 1;
					else
						_v[0xF] = 0;
					_v[x] = _v[x] - _v[y];

					#if DEBUG
					std::cout<<"\nSUB Vx, Vy";
					std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
					std::cout<<"\nV["<<std::hex<<y<<"] : "<<(int)_v[y];
					std::cout<<"\nV[0xF] : "<<(int)_v[0xF];
					#endif
					break;
				}

				case(0x6):  //SHR Vx {, Vy}
				{
					if((_v[x] & 0x01) == 1)
						_v[0xF] = 1;
					else
						_v[0xF] = 0;
					_v[x] /= 2;
					
					#if DEBUG
					std::cout<<"\nSHR Vx {, Vy}";
					std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
					std::cout<<"\nV[0xF] : "<<(int)_v[0xF];
					#endif
					break;
				}

				case(0x7):  //SUBN Vx, Vy
				{
					if(_v[y] > _v[x])
						_v[0xF] = 1;
					else
						_v[0xF] = 0;
					_v[x] = _v[y] - _v[x];
					
					#if DEBUG
					std::cout<<"\nSUBN Vx, Vy";
					std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
					std::cout<<"\nV["<<std::hex<<y<<"] : "<<(int)_v[y];
					std::cout<<"\nV[0xF] : "<<(int)_v[0xF];
					#endif
					break;
				}

				case(0xE):  //SHL Vx {, Vy}
				{
					if((_v[x] & 0x80) ==1)
						_v[0xF] = 1;
					else
						_v[0xF] = 0;
					_v[x] = _v[x] * 2;
					
					#if DEBUG
					std::cout<<"\nSHL Vx {, Vy}";
					std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
					std::cout<<"\nV[0xF] : "<<(int)_v[0xF];
					#endif
					break;
				}
			}
			break;
		}

		case(0x9):  //9xy0 - SNE Vx, Vy
		{
			if(_v[x] != _v[y])
				_pc += 2;
			
			#if DEBUG
			std::cout<<"\n9xy0 - SNE Vx, Vy";
			std::cout<<"\nV["<<std::hex<<x<<"] : "<<(int)_v[x];
			std::cout<<"\nV["<<std::hex<<y<<"] : "<<(int)_v[y];
			std::cout<<"\n_pc : "<<std::hex<<(int)_pc;
			#endif
			break;
		}

		case(0xA):  //Annn - LD I, addr
		{
			_i = nnn;

			#if DEBUG
			std::cout<<"\nAnnn - LD I, addr";
			std::cout<<std::hex<<(int)_i;
			#endif
			break;
		}

		case(0xD):  //Dxyn - DRW Vx, Vy, nibble
		{
			_v[0xF] = 0;
			for(int row=0; row<n; row++)
			{
				uint8_t spriteData = _memory[_i + row];
				for(int col=0; col<8; col++)
				{
					int xCordinate = (_v[x] + col) % SCREEN_WIDTH;
					int yCordinate = (_v[y] + row) % SCREEN_HEIGHT;

					if( (spriteData & (0x80 >> col)) !=0)
					{
						if(_display.getPixel(xCordinate, yCordinate) == 1)
						{
							_display.setPixel(xCordinate, yCordinate, 0);
							_v[0xF] = 1;
						}
						else
						{
							_display.setPixel(xCordinate, yCordinate, 1);
std::cerr<<"\nSetting "<<xCordinate<<" "<<yCordinate<<" to 1";
						}
					}
				}
			}
			_updateDisplay = true;

			#if DEBUG
			std::cout<<"\nCLI graphics\n";
			for(int row=0; row<SCREEN_HEIGHT; row++)
			{
				for(int col=0; col<SCREEN_WIDTH; col++)
				{
					std::cout<<std::hex<<(int)_display.getPixel(col, row);
				}
				std::cout<<"\n";
			}
			#endif
			break;
		}

		default: 
			std::cerr<<"\nCannot recognize instruction : "<<std::hex<<int(opcode);
			 exit(1);
	}
}

uint16_t Chip8::fetch()
{
	uint16_t opcodeFirstHalf = _memory[_pc]<<8;
	uint16_t opocodeSecondHalf = _memory[_pc+1];
	uint16_t opcode = opcodeFirstHalf | opocodeSecondHalf;
	_pc +=2;
	return opcode;
}

void Chip8::runCycle()
{
	uint16_t opcode = fetch();

	#if DEBUG
	std::cout<<"\nRunning cycle for opcode : "<<std::hex<<(int)opcode;
	#endif

	decodeAndExecute(opcode);

	if(_updateDisplay)
	{
std::cerr<<"\nDisplaying screen";
		_display.updateScreen();
		_updateDisplay = false;
	}
	_quitGameLoop = _display.quitGameLoop();
}

bool Chip8::quitGameLoop()
{
	return _quitGameLoop;
}
