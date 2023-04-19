#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <vector>
#include "color.hpp"

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

const std::vector<ColorCombo> colorComboList
{
	ComboPallete::green_mossGreen,	
	ComboPallete::blue_pink,
	ComboPallete::blue_peach,
	ComboPallete::black_yellow,
	ComboPallete::red_yellow,
	ComboPallete::limeGreen_blue,
	ComboPallete::lavender_teal,
	ComboPallete::cherryRed_offWhite,
	ComboPallete::babyBlue_white,
	ComboPallete::hotPink_cyan,
	ComboPallete::cherryRed_lightPink,
	ComboPallete::red_spicedApple,
	ComboPallete::lightPurple_mint,
	ComboPallete::black_white,
	ComboPallete::white_black,
	ComboPallete::orange_black,
//	ComboPallete::,
};

struct Config
{
	const Version currVersion{CHIP_48};
	const int volume{3000};
	const int instructionsPerSecond{900};
	const int framesPerSecond{60};
	int gameState{RUNNING};
	ColorCombo currentCombo{colorComboList[0]};
};
extern Config configurations;

#endif
