#include "display.h"
#include <iostream>

#define DEBUG true

Display::Display():
	_pixel{}
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH*SCREEN_SCALE, SCREEN_HEIGHT*SCREEN_SCALE, 0,&_window, &_renderer );
	SDL_RenderSetScale(_renderer, SCREEN_SCALE, SCREEN_SCALE);
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

	
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
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
	for(int row=0; row<SCREEN_HEIGHT; row++)
	{
		for(int col=0; col<SCREEN_WIDTH; col++)
		{
			if(_pixel[col][row])
			{
				SDL_SetRenderDrawColor(_renderer, 255, 100, 0, 255);
				SDL_RenderDrawPoint(_renderer, col, row);

				if(col == 31 && row == 0)
					std::cerr<<"\nERROR";
			}
		}
	}
	SDL_RenderPresent(_renderer);
}

bool Display::quitGameLoop()
{
	//SDL_Event is a union that contains structures for
	//all event types in SDL2
	SDL_Event event;

	//SDL_PollEvent() reads an event from top of queue
	//into 'event'
	//It returns 0 if queue is empty, 1 otherwise
	while(SDL_PollEvent(&event) != 0)
	{
		if(event.type == SDL_QUIT)
			return true;
	}
	return false;
}
