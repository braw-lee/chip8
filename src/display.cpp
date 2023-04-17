#include "../include/display.hpp"
#include "../include/config.hpp"

#include <iostream>

#define DEBUG true

Display::Display():
	_pixel{}
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	_window = SDL_CreateWindow("CHIP_8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH*SCREEN_SCALE, SCREEN_HEIGHT*SCREEN_SCALE, 0);
	_renderer = SDL_CreateRenderer(_window, 1, 0);
	SDL_RenderSetScale(_renderer, SCREEN_SCALE, SCREEN_SCALE);

	if(_window == nullptr)
		std::cerr<<"\nError creating SDL window : "<<SDL_GetError();
	if(_renderer == nullptr)
		std::cerr<<"\nError creating SDL renderer : "<<SDL_GetError();	

	clear();
}

Display::~Display()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	_window = nullptr;
	_renderer = nullptr;

	SDL_Quit();
}

void Display::clear()
{
	for(int row=0; row<SCREEN_HEIGHT; row++)
	{
		for(int col=0; col<SCREEN_WIDTH; col++)
		{	
			_pixel[col][row] = 0;
		}
	}
	SDL_SetRenderDrawColor(_renderer, configurations.currentCombo.bg.red_val, configurations.currentCombo.bg.green_val, configurations.currentCombo.bg.blue_val, 255);
	SDL_RenderClear(_renderer);

	#if DEBUG
	std::cout<<"\nCLS";	
	#endif
}

uint8_t Display::getPixel(int x,int y)
{
	return _pixel[x][y];
}

void Display::setPixel(int x, int y, int val)
{
	_pixel[x][y] = val;
}

void Display::updateScreen()
{
	SDL_SetRenderDrawColor(_renderer, configurations.currentCombo.bg.red_val, configurations.currentCombo.bg.green_val, configurations.currentCombo.bg.blue_val, 255);
	SDL_RenderClear(_renderer);
	for(int row=0; row<SCREEN_HEIGHT; row++)
	{
		for(int col=0; col<SCREEN_WIDTH; col++)
		{
			if(_pixel[col][row])
			{
				SDL_SetRenderDrawColor(_renderer, configurations.currentCombo.fg.red_val, configurations.currentCombo.fg.green_val, configurations.currentCombo.fg.blue_val, 255);
				SDL_RenderDrawPoint(_renderer, col, row);
			}
		}
	}
	SDL_RenderPresent(_renderer);
}

