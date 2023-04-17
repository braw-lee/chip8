#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

enum Version
{
	ORIGINAL,
	CHIP_48
};

enum GameState
{
	PAUSED,
	RUNNING
};

struct ColorCombo
{
	//foreground color , default orange
	uint8_t fg_red{0};
	uint8_t fg_green{0};
	uint8_t fg_blue{255};

	//background color , default black
	uint8_t bg_red{255};
	uint8_t bg_green{255};
	uint8_t bg_blue{255};
};

struct Config
{
	Version currVersion{CHIP_48};
	int volume{3000};
	int instructionsPerSecond{900};
	int framesPerSecond{60};
	int gameState{RUNNING};
	ColorCombo currentCombo{};
};

extern Config configurations;

#endif
