#include "analog_input.h"

#include <fstream>

namespace sensors {

f32 analog_pin(u32 number)
{
	std::string path{"/sys/bus/iio/devices/iio:device0/in_voltage" + std::to_string(number) +
	                 "_raw"};

	std::ifstream file{path};
	if (!file.is_open())
	{
		throw std::runtime_error{"cannot open file " + path};
	}

	u32 value;
	file >> value;

	return static_cast<f32>(value) * 1.8f / 4095.f;
}

f32 before_voltage_divider(f32 voltage)
{
	return voltage / (18.f / (18.f + 33.f));
}

} // namespace sensor
