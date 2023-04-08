#include "utility.h"
#include <cctype>
#include <sstream>
#include <algorithm>

std::string Utility::toHex(int x, int length)
{
	std::stringstream stream;
	stream <<std::hex<< x;

	std::string output {stream.str()};
	std::transform(output.begin(), output.end(), output.begin(), ::toupper);
	while(output.size() < length)
		output = "0" + output;
	output = "0x" + output;

	return output;
}
