#include "sensors.h"

#include <fstream>
#include <gpiod.hpp>
#include <unistd.h>

namespace sensors {

namespace {

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

f32 before_voltage_divider(f32 volts)
{
	return volts / (18.f / (18.f + 33.f));
}

gpiod::chip chip;
gpiod::line line;

f32 measure_dust()
{
	line.set_value(1);
	usleep(280);
	f32 volts{analog_pin(3)};
	line.set_value(0);

	f32 millivolts{before_voltage_divider(volts) * 1000.f};
	if (millivolts > 600.f)
	{
		return (millivolts - 600.f) * 0.2f;
	}

	return 0.f;
}

} // namespace

void init()
{
	chip.open("gpiochip3");

	gpiod::line_request config{};
	config.request_type = gpiod::line_request::DIRECTION_OUTPUT;
	config.consumer = "Consumer";

	line = chip.get_line(1);
	line.request(config);
	line.set_value(0);
}

f32 water_temperature()
{
	f32 volts{analog_pin(1)};
	return 25.f + (volts - 0.75f) / 0.01f;
}

f32 water_turbidity()
{
	f32 volts{before_voltage_divider(analog_pin(0))};
	return -1120.4f * volts * volts + 5742.3f * volts - 4352.9f;
}

f32 atmospheric_dust()
{
	f32 avg_dust{};
	for (u32 i = 0; i < 10;)
	{
		f32 dust{measure_dust()};
		if (dust > 0.f)
		{
			avg_dust += dust;
			++i;
			usleep(50000);
		}
	}
	avg_dust /= 10.f;

	return avg_dust;
}

} // namespace sensors
