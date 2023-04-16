#ifndef CONFIG_H
#define CONFIG_H

enum Version
{
	ORIGINAL,
	CHIP_48
};

struct Config
{
	Version currVersion{CHIP_48};
	int volume{3000};
	int instructionsPerSecond{700};
};


static Config configurations;

#endif
