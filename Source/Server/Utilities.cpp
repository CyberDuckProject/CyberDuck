#include "Utilities.h"

#include <sys/stat.h>

namespace utl
{
	bool exists(const std::string& path)
	{
		struct stat buffer;
		return stat(path.c_str(), &buffer) == 0;
	}
}
