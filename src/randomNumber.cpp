#include "../include/randomNumber.hpp"
#include <random>

int RandomNumber::generateRandomNumber(int x, int y)
{
	std::random_device rd;  //used to obtain seed for random engine
	std::mt19937 mt(rd());  //mt engine is seeded
	std::uniform_int_distribution<> generate(x,y);
	return generate(mt);
}
