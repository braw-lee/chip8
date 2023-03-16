#ifndef DISPLAY_H
#define DISPLAY_H

#include<array>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;
const int SCREEN_SCALE = 25;

class Display
{
public:
	Display();
	~Display();
	void clear();
	uint8_t getPixel(int x,int y);
	void setPixel(int x, int y, int val);
	void updateScreen();
	bool quitGameLoop();
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::array<std::array<uint8_t, SCREEN_HEIGHT>, SCREEN_WIDTH> _pixel;	
//	uint8_t _pixel[SCREEN_WIDTH][SCREEN_HEIGHT];
};

#endif
