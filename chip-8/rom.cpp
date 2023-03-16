#include "rom.h"
#include <fstream>

void Rom::setPath(std::string& path)
{
	_path = path;
}

void Rom::processData()
{
	std::ifstream file(_path, std::ios::binary | std::ios::in);

	if(!file.is_open())
		
}
