#ifndef CONFIG_H
#define CONFIG_H

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

struct Config
{
	Version currVersion{CHIP_48};
	int volume{3000};
	int instructionsPerSecond{700};
	int framesPerSecond{60};
	int gameState{0};
};


static Config configurations;

#endif
