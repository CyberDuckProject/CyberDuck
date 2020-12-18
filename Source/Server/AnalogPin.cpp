#include "AnalogPin.h"

#include "Utilities.h"

namespace
{
	u32 to_millivolts(const u32 raw_input)
	{
		return raw_input * 736 / 1693; // TODO: verify this
	}
}

analog_pin::analog_pin(const u32 number)
    : path{"/sys/bus/iio/devices/iio:device0/in_voltage" + std::to_string(number) + "_raw"}
{
	if (!utl::exists(path))
	{
		// TODO: error handling
	}
}

u32 analog_pin::millivolts() const
{
	return to_millivolts(utl::read_one<u32>(path));
}

f32 analog_pin::volts() const
{
	return static_cast<f32>(millivolts()) / 1000.0f;
}
