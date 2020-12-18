#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <string>

namespace utl
{
	bool exists(const std::string& path);

	template<typename value_type>
	value_type read_one(const std::string& path)
	{
		std::ifstream file{path};
		value_type result;
		file >> result;
		return result;
	}
}

#endif
