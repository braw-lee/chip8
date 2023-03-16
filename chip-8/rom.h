#include <string>
#include <vector>

class Rom
{
public:
	void setPath(std::string& path);
	void processData();
	std::vector<uint8_t> getData();
private:
	std::string _path;
	std::vector<uint8_t> _data;
};
