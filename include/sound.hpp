#ifndef SOUND_HPP
#define SOUND_HPP

#include <SDL2/SDL_audio.h>
#include <iostream>

class Sound
{
public:
	Sound();
	~Sound();
	void pause();
	void unpause();
private:
	const int _amplitude;
	const int _frequency;

	SDL_AudioDeviceID _dev;
};

#endif
