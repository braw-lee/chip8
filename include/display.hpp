#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include<array>
#include<string>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;
const int SCREEN_SCALE = 25;

class Display
{
public:
	enum PixelState
	{
		PIXEL_OFF,
		PIXEL_ON
	};

	Display();
	~Display();
	void clear();
	PixelState getPixel(int x,int y);
	void setPixel(int x, int y, PixelState state);
	void updateScreen();
	void updateWindowName(const char* newName);
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::array<std::array<PixelState, SCREEN_HEIGHT>, SCREEN_WIDTH> _pixel;
};

#endif
