#ifndef COLOR_HPP
#define COLOR_HPP

#include <array>
#include <cstdint>

struct Color
{
	//default value black #000
	uint8_t red_val{0};
	uint8_t green_val{0};
	uint8_t blue_val{0};
};

struct ColorCombo
{
	//default value back and white
	Color fg{0, 0, 0};
	Color bg{0xFF, 0xFF, 0xFF};
};

namespace ColorPallete
{
	const Color black	{0x00, 0x00, 0x00};
	const Color blue	{0x00, 0x53, 0x9C};
	const Color peach	{0xEE, 0xA4, 0x7F};
	const Color lightPink	{0xFB, 0xEA, 0xEB};
	const Color yellow	{0xFE, 0xE7, 0x15};
	const Color red		{0xF9, 0x61, 0x67};
	const Color limeGreen	{0xCC, 0xF3, 0x81};
	const Color lavender	{0xE2, 0xD1, 0xF9};
	const Color teal	{0x31, 0x77, 0x73};
	const Color cherryRed	{0x99, 0x00, 0x11};
	const Color offWhite	{0xFC, 0xF6, 0xFF};
	const Color babyBlue	{0x8A, 0xAA, 0xE5};
	const Color white	{0xFF, 0xFF, 0xFF};
	const Color hotPink	{0xFF, 0x69, 0xB4};
	const Color cyan	{0x00, 0xFF, 0xFF};
	const Color spicedApple	{0x78, 0x39, 0x37};
	const Color lightPurple	{0xAA, 0x96, 0xDA};
	const Color mint	{0xC5, 0xFA, 0xD5};
	const Color green	{0x2C, 0x5F, 0x2D};
	const Color mossGreen	{0x97, 0xBC, 0x62};
	const Color orange	{0xFF, 0x64, 0x00};
//	const Color {0x, 0x, 0x};
}

namespace ComboPallete
{
	const ColorCombo blue_peach		{ColorPallete::blue, ColorPallete::peach};
	const ColorCombo blue_pink		{ColorPallete::blue, ColorPallete::lightPink};
	const ColorCombo black_yellow		{ColorPallete::black, ColorPallete::yellow};
	const ColorCombo red_yellow		{ColorPallete::red, ColorPallete::yellow};
	const ColorCombo limeGreen_blue		{ColorPallete::limeGreen, ColorPallete::blue};
	const ColorCombo lavender_teal		{ColorPallete::lavender, ColorPallete::teal};
	const ColorCombo cherryRed_offWhite	{ColorPallete::cherryRed, ColorPallete::offWhite};
	const ColorCombo babyBlue_white		{ColorPallete::babyBlue, ColorPallete::white};
	const ColorCombo hotPink_cyan		{ColorPallete::hotPink, ColorPallete::cyan};
	const ColorCombo cherryRed_lightPink	{ColorPallete::cherryRed, ColorPallete::lightPink};
	const ColorCombo red_spicedApple	{ColorPallete::red, ColorPallete::spicedApple};
	const ColorCombo lightPurple_mint	{ColorPallete::lightPurple, ColorPallete::mint};
	const ColorCombo green_mossGreen	{ColorPallete::green, ColorPallete::mossGreen};
	const ColorCombo black_white		{ColorPallete::black, ColorPallete::white};
	const ColorCombo white_black		{ColorPallete::white, ColorPallete::black};
	const ColorCombo orange_black		{ColorPallete::orange, ColorPallete::black};
//	const ColorCombo {ColorPallete::, ColorPallete::};
}

#endif
