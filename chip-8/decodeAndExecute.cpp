#include "chip8.h"
#include "utility.h"

#include <iostream>
#include <cstdlib>

using namespace Utility;

void Chip8::decodeAndExecute(uint16_t opcode)
{
	uint8_t x = (opcode & 0x0F00)>>8;  //second nibble
	uint8_t y = (opcode & 0x00F0)>>4;  //third nibble
	uint8_t n = (opcode & 0x000F);     //fourth nibble
	uint8_t nn = (opcode & 0x00FF);    //third and fourth nibble
	uint16_t nnn = (opcode & 0x0FFF);  //second, third and fourth nibble
	
	#if DEBUG
	std::cout<<"\nopcode : "<<toHex(opcode, 4);
	std::cout<<"\nx : "<<toHex(x, 1);
	std::cout<<"\ny : "<<toHex(y, 1);
	std::cout<<"\nn : "<<toHex(n, 1);
	std::cout<<"\nnn : "<<toHex(nn, 2);
	std::cout<<"\nnnn : "<<toHex(nnn, 3);
	#endif

	//test first nibble
	switch(opcode>>12)
	{
		//instructions with first nibble as 0x0
		case(0x0):
		{
			switch(nn)
			{
				case(0xE0):  //00E0 - CLS
				{
					_display.clear();
					_updateDisplay = true;

					#if DEBUG
					std::cout<<"\n00E0 - CLS";
					#endif
					break;
				}
				case(0xEE):  //00EE - RET
				{
					_pc = _stack[_sp];
					_sp--;

					#if DEBUG
					std::cout<<"\n00EE - RET";
					std::cout<<"\n_pc : "<<Utility::toHex(_pc,4);
					std::cout<<"\n_sp : "<<Utility::toHex(_sp, 2);
					#endif
					break;
				}

				default:
					panicQuit(opcode);
			}
			break;
		}
		
		case(0x1):  //1nnn - JP addr
		{
			_pc = nnn;

			#if DEBUG
			std::cout<<"\n1nnn - JP addr";
			std::cout<<"\n_pc : "<<Utility::toHex(_pc, 4);
			#endif
			break;
		}

		case(0x2):  //2nnn - CALL addr
		{
			_sp++;
			_stack[_sp] = _pc;
			_pc = nnn;

			#if DEBUG
			std::cout<<"\n2nnn - CALL addr";
			std::cout<<"\n_sp : "<<Utility::toHex(_sp, 2);
			std::cout<<"\n_stack[_sp] : "<<Utility::toHex(_stack[_sp], 4);
			std::cout<<"\n_pc : "<<Utility::toHex(_pc, 4);
			#endif
			break;
		}

		case(0x3):  //3xkk - SE Vx, byte
		{
			if(_v[x] == nn)
				_pc += 2;

			#if DEBUG
			std::cout<<"\n3xkk - SE Vx, byte";
			std::cout<<"\nV["<<Utility::toHex(x, 1)<<"] : "<<Utility::toHex(_v[x], 2);
			std::cout<<"\nnn : "<<Utility::toHex(nn, 2);
			std::cout<<"\n_pc : "<<Utility::toHex(_pc, 4);
			#endif
			break;
		}

		case(0x4):  //4xkk - SNE Vx, byte
		{
			if(_v[x] != nn)
				_pc += 2;

			#if DEBUG
			std::cout<<"\n4xkk - SNE Vx, byte";
			std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
			std::cout<<"\n_pc : "<<toHex(_pc, 4);
			#endif
			break;
		}

		case(0x5):  //5xy0 - SE Vx, Vy
		{
			if(_v[x] == _v[y])
				_pc += 2;

			#if DEBUG
			std::cout<<"\n5xy0 - SE Vx, Vy";
			std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
			std::cout<<"\nV["<<toHex(y, 1)<<"] : "<<toHex(_v[y], 2);
			std::cout<<"\n_pc : "<<toHex(_pc, 4);
			#endif
			break;
		}

		case(0x6):  //6xkk - LD Vx, byte
		{
			_v[x] = nn;
			
			#if DEBUG
			std::cout<<"\n6xkk - LD Vx, byte";
			std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
			#endif
			break;
		}

		case(0x7):  //7xkk - ADD Vx, byte
		{
			_v[x] = _v[x] + nn;

			#if DEBUG
			std::cout<<"\n7xkk - ADD Vx, byte";
			std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
			#endif
			break;
		}

		case(0x8):
		{
			switch(n)
			{
				case(0x0):  //8xy0 - LD Vx, Vy
				{
					_v[x] = _v[y];

					#if DEBUG
					std::cout<<"\n8xy0 - LD Vx, Vy";
					std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
					std::cout<<"\nV["<<toHex(y, 1)<<"] : "<<toHex(_v[y], 2);
					#endif
					break;
				}

				case(0x1):  //8xy1 - OR Vx, Vy
				{
					_v[x] = _v[x] | _v[y];
					
					//For CHIP-8 only
					_v[0xF] = 0;

					#if DEBUG
					std::cout<<"\n8xy1 - OR Vx, Vy";
					std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
					std::cout<<"\nV["<<toHex(y, 1)<<"] : "<<toHex(_v[y], 2);
					#endif
					break;
				}

				case(0x2):  //8xy2 - AND Vx, Vy
				{
					_v[x] = _v[x] & _v[y];
					
					//For CHIP-8 only
					_v[0xF] = 0;

					#if DEBUG
					std::cout<<"\n8xy2 - AND Vx, Vy";
					std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
					std::cout<<"\nV["<<toHex(y, 1)<<"] : "<<toHex(_v[y], 2);
					#endif
					break;
				}

				case(0x3):  //8xy3 - XOR Vx, Vy
				{
					_v[x] = _v[x] ^ _v[y];

					//For CHIP-8 only
					_v[0xF] = 0;

					#if DEBUG
					std::cout<<"\n8xy3 - XOR Vx, Vy";
					std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
					std::cout<<"\nV["<<toHex(y, 1)<<"] : "<<toHex(_v[y], 2);
					#endif
					break;
				}

				case(0x4):  //8xy4 - ADD Vx, Vy
				{
					uint8_t flag = uint16_t(_v[x] + _v[y]) > 0xFF;
					_v[x] = _v[x] + _v[y];
					_v[0xF] = flag;

					#if DEBUG
					std::cout<<"\n8xy4 - ADD Vx, Vy";
					std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
					std::cout<<"\nV["<<toHex(y, 1)<<"] : "<<toHex(_v[y], 2);
					std::cout<<"\nV[0xF] : "<<toHex(_v[0xF], 2);
					#endif
					break;
				}

				case(0x5):  //8xy5 - SUB Vx, Vy
				{
					uint8_t flag = _v[x] > _v[y];
					_v[x] = _v[x] - _v[y];
					_v[0xF] = flag;

					#if DEBUG
					std::cout<<"\n8xy5 - SUB Vx, Vy";
					std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
					std::cout<<"\nV["<<toHex(y, 1)<<"] : "<<toHex(_v[y], 2);
					std::cout<<"\nV[0xF] : "<<toHex(_v[0xF], 2);
					#endif
					break;
				}

				case(0x6):  //8xy6 - SHR Vx {, Vy}
				{
					//For CHIP-8
					uint8_t flag = _v[y] & 0x1;
					_v[x] = _v[y] >> 1;
					_v[0xF] = flag;
					
				//	uint8_t flag = _v[x] & 0x1;  //for other versions
				//	_v[x] /= 2;
				//	_v[0xF] = flag;
					
					#if DEBUG
					std::cout<<"\n8xy6 - SHR Vx {, Vy}";
					std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
					std::cout<<"\nV[0xF] : "<<toHex(_v[0xF], 2);
					#endif
					break;
				}

				case(0x7):  //8xy7 - SUBN Vx, Vy
				{
					uint8_t flag = _v[y] > _v[x];
					_v[x] = _v[y] - _v[x];
					_v[0xF] = flag;

					#if DEBUG
					std::cout<<"\n8xy7 - SUBN Vx, Vy";
					std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
					std::cout<<"\nV["<<toHex(y, 1)<<"] : "<<toHex(_v[y], 2);
					std::cout<<"\nV[0xF] : "<<toHex(_v[0xF], 2);
					#endif
					break;
				}

				case(0xE):  //8xyE - SHL Vx {, Vy}
				{
					//For CHIP-8
					uint8_t flag = _v[y] >> 7;
					_v[x] = _v[y] << 1;
					_v[0xF] = flag;
					
				//	uint8_t flag = _v[x] >> 7;  //for other versions
				//	_v[x] = _v[x] * 2;
				//	_v[0xF] = flag;
					
					#if DEBUG
					std::cout<<"\n8xyE - SHL Vx {, Vy}";
					std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
					std::cout<<"\nV[0xF] : "<<toHex(_v[0xF], 2);
					#endif
					break;
				}

				default:
					panicQuit(opcode);
			}
			break;
		}

		case(0x9):  //9xy0 - SNE Vx, Vy
		{
			if(_v[x] != _v[y])
				_pc += 2;
			
			#if DEBUG
			std::cout<<"\n9xy0 - SNE Vx, Vy";
			std::cout<<"\nV["<<toHex(x, 1)<<"] : "<<toHex(_v[x], 2);
			std::cout<<"\nV["<<toHex(y, 1)<<"] : "<<toHex(_v[y], 2);
			std::cout<<"\n_pc : "<<toHex(_pc, 4);
			#endif
			break;
		}

		case(0xA):  //Annn - LD I, addr
		{
			_i = nnn;

			#if DEBUG
			std::cout<<"\nAnnn - LD I, addr";
			std::cout<<"\n_i : "<<toHex(_i, 4);
			#endif
			break;
		}

		case(0xB):  //Bnnn - JP V0, addr
		{
			_pc = _v[0] + nnn;

			#if DEBUG
			std::cout<<"\nBnnn - JP V0, addr";
			std::cout<<"\nSet _pc to : "<<toHex(_pc, 4);
			#endif
			break;
		}

		case(0xC):  //Cxkk - RND Vx, byte
		{
			uint8_t ran = RandomNumber::generateRandomNumber(0,255);
			_v[x] = ran & nn;

			#if DEBUG
			std::cout<<"\nCxkk - RND Vx, byte";
			std::cout<<"\nRandom number generated : "<<toHex(ran, 2);
			std::cout<<"\n_v[x] set to : "<<toHex(_v[x], 2);
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
							_v[0xF] = 1;
						}
						
						_display.setPixel(xCordinate, yCordinate, _display.getPixel(xCordinate, yCordinate) ^ 1);
					}
					//when sprite does not start outside of screen
					//but some part goes out, it is clipped
					if(_v[x] < SCREEN_WIDTH && (_v[x] + col) >= SCREEN_WIDTH)
						break;
				}
				//when sprite does not start outside of screen
				//but some part goes out, it is clipped
				if(_v[y] < SCREEN_HEIGHT && (_v[y] + row) >= SCREEN_HEIGHT)
					break;
			}
			_updateDisplay = true;

			#if DEBUG
			std::cout<<"\nCLI graphics\n";
			for(int row=0; row<SCREEN_HEIGHT; row++)
			{
				for(int col=0; col<SCREEN_WIDTH; col++)
				{
					if(_display.getPixel(col, row))
							std::cout<<1;
					else
						std::cout<<" ";
				}
				std::cout<<"\n";
			}
			#endif
			break;
		}
		
		case(0xE):  //input
		{
			switch(nn)
			{
				case(0x9E): //Ex9E - SKP Vx
				{
					if(_keyState[_v[x]] == Keyboard::KEY_DOWN)
						_pc += 2;

					#if DEBUG
					std::cout<<"\nEx9E - SKP Vx";
					std::cout<<"\nIncrement _pc to : "<<toHex(_pc, 4);
					#endif
					break;
				}

				case(0xA1): //ExA1 - SKNP Vx
				{
					if(_keyState[_v[x]] == Keyboard::KEY_UP)
						_pc += 2;

					#if DEBUG
					std::cout<<"\nExA1 - SKNP Vx";
					std::cout<<"\nIncrement _pc to : "<<toHex(_pc, 4);
					#endif
					break;
				}

				default:
					panicQuit(opcode);
			}
			break;
		}

		case(0xF):
		{
			switch(nn)
			{
				case(0x07):  //Fx07- LD Vx, DT
				{
					_v[x] = _delayTimer;

					#if DEBUG
					std::cout<<"\nFx07 - LD Vx, DT";
					std::cout<<"\nSet _v[x] to _delayTimer : "<<toHex(_v[x], 2);
					#endif
					break;
				}

				case(0x0A):  //Fx0A - LD Vx, K
				{
					uint8_t key{};
					bool waitForInput{true};
					for(int i=0; i< 16; i++)
					{
						if(_keyState[i] == Keyboard::KEY_DOWN)
						{
							key = i;
							waitForInput = false;
							break;
						}
					}
					if(waitForInput)
						_pc -= 2;
					else
						_v[x] = key;
					#if DEBUG
					std::cout<<"\nFx0A - LD Vx, K";
					if(waitForInput)
						std::cout<<"\nWaiting for input from user";
					else
						std::cout<<"\n_v[x] set to : "<<toHex(_v[x], 2);
					#endif
					break;
				}

				case(0x15):  //Fx15 - LD DT, Vx
				{
					_delayTimer = _v[x];

					#if DEBUG
					std::cout<<"\nFx15 - LD DT, Vx";
					std::cout<<"\nDelay timer is set to : "<<toHex(_delayTimer, 2);
					#endif
					break;
				}

				case(0x18):  //Fx18 - LD ST, Vx
				{
					_soundTimer = _v[x];

					#if DEBUG
					std::cout<<"\nFx18 - LD ST, Vx";
					std::cout<<"\nSound timer is set to : "<<toHex(_soundTimer, 2);
					#endif
					break;
				}

				case(0x1E):  //Fx1E - ADD I, Vx
				{
					_i += _v[x];

					#if DEBUG
					std::cout<<"\nFx1E - ADD I, Vx";
					std::cout<<"\nSet _i to : "<<toHex(_i, 4);
					#endif
					break;
				}

				case(0x29):  //Fx29 - LD F, Vx
				{
					//check cpu's constructor
					//0 is stored at 0th index
					//and it takes 5 indexes
					//so 1 is stored at 5th index
					//
					//Similarly sprite for every number
					//is placed at (number * 5) index 
					_i = _v[x] * 5;

					#if DEBUG
					std::cout<<"\nFx29 - LD F, Vx";
					std::cout<<"\n_i is set to sprite of digit/alphabet : "<<toHex(_v[x], 2);
					std::cout<<"\n_i : "<<toHex(_i, 4);
					#endif
					break;
				}

				case(0x33):  //Fx33 - LD B, Vx
				{
					_memory[_i] = _v[x] / 100;
					_memory[_i+1] = (_v[x] / 10) % 10;
					_memory[_i+2] = _v[x] % 10;

					#if DEBUG
					std::cout<<"\nFx33 - LD B, Vx";
					std::cout<<"\n_v[x] in decimal : "<<toHex(_v[x], 2);
					std::cout<<"\n_memory[_i] , _memory[_i+1] , _memory[_i+2] set to : "<<toHex(_memory[_i], 2)<<" "<<toHex(_memory[_i+1], 2)<<" "<<toHex(_memory[_i+2], 2);
					#endif
					break;
				}

				case(0x55):  //Fx55 - LD [I], Vx
				{
					//For CHIP-8
					for(int i=0; i<=x; i++)
					{
						_memory[_i] = _v[i];
						_i++;
					}

					#if DEBUG
					std::cout<<"\nFx55 - LD [I], Vx";
					for(int i=0; i<=x; i++)
						std::cout<<"\n_memory["<<toHex(_i+i, 4)<<"] : "<<toHex(_memory[_i + i], 2);
					#endif
					break;
				}

				case(0x65):  //Fx65 - LD Vx, [I]
				{
					for(int i=0; i<=x; i++)
					{
						_v[i] = _memory[_i + i];
					}

					#if DEBUG
					std::cout<<"\nFx65 - LD Vx, [I]";
					for(int i=0; i<=x; i++)
						std::cout<<"\n_v["<<toHex(i, 1)<<"] : "<<toHex(_v[i], 2);
					#endif
					break;
				}
				
				default:
					panicQuit(opcode);
			}
			break;
		}

		default:
			panicQuit(opcode);
	}
}

