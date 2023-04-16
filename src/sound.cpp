#include "../include/sound.h"
#include "../include/config.h"

void callBackFunction(void* userData, uint8_t* stream, int len)
{
	static uint32_t running_sample_index = 0;
	const int32_t square_wave_period = 44100 / 256;
	const int32_t half_square_wave_period = square_wave_period / 2;
	for(int i=0; i<len/2; i++)
	{
		stream[i] = ((running_sample_index++ / half_square_wave_period) % 2 ? configurations.volume : -configurations.volume);
	}
}

Sound::Sound() : _amplitude{28000}, _frequency{44100}
{
	SDL_AudioSpec want, have;
	SDL_memset(&want, 0, sizeof(want));

	want.freq = _frequency;
	want.format = AUDIO_S16LSB;
	want.channels = 1;
	want.samples = 1024;
	want.callback = callBackFunction;

	_dev = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
	std::cout<<"devID : "<<_dev;
	if(_dev == 0)
		std::cerr<<"\n\nCouldnot initialize audio device because : "<<SDL_GetError();
}

Sound::~Sound()
{
	SDL_CloseAudioDevice(_dev);
}

void Sound::pause()
{
	SDL_PauseAudioDevice(_dev, 1);
}

void Sound::unpause()
{
	SDL_PauseAudioDevice(_dev, 0);
}
