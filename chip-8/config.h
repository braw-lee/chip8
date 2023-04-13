#ifndef CONFIG_H
#define CONFIG_H

namespace Config
{
	enum Version
	{
		ORIGINAL,
		CHIP_48
	};

	static Version currVersion{CHIP_48};
}

#endif
