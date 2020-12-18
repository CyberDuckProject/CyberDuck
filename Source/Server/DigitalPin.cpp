#include "DigitalPin.h"

#include "Utilities.h"
#include <cassert>

namespace
{
	template<typename value_type>
	void write(const value_type& value, const std::string& path)
	{
		std::fstream file{path};
		if (!file.is_open())
		{
			// TODO: error handling
		}

		file << value;
	}
}

digital_pin::digital_pin(const u32 number)
    : value_path{"/sys/class/gpio/gpio" + std::to_string(number) + "/value"}
{
	// Create port
	if (!utl::exists(value_path))
	{
		write(number, "/sys/class/gpio/export");
	}
	if (!utl::exists(value_path))
	{
		// TODO: error handling
	}

	// Configure it for output
	write("none", "/sys/class/gpio/gpio" + std::to_string(number) + "/edge");
	write("out", "/sys/class/gpio/gpio" + std::to_string(number) + "/direction");

	// Disable by default
	set_value(false);
}

bool digital_pin::value() const
{
	return utl::read_one<char>(value_path) == '1';
}

void digital_pin::set_value(const bool value)
{
	write(value ? '1' : '0', value_path);
}
