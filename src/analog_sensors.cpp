#include "analog_sensors.h"

#include <cassert>
#include <fstream>
#include <cstdint>
#include <gpiod.hpp>
#include <unistd.h>

namespace {

float analog_pin_volts(uint32_t number)
{
	assert(number <= 7);

	std::ifstream file{"/sys/bus/iio/devices/iio:device0/in_voltage" + std::to_string(number) +
	                   "_raw"};
	assert(file.is_open());

	uint32_t value;
	file >> value;

	constexpr float multiplier{1.8f / 4095.f};
	return static_cast<float>(value) * multiplier;
}

float calculate_turbidity(float voltage)
{
	return -1120.4f * voltage * voltage + 5742.3f * voltage - 4352.9f;
}

float calculate_dust(float voltage)
{
	constexpr float base_voltage{0.9f};
	constexpr float step_volts{0.5f};
	constexpr float step_value{0.1f};

	return (voltage - base_voltage) / step_volts * step_value;
}

} // namespace

float atmospheric_dust()
{
	gpiod::chip chip{"gpiochip3"};
	gpiod::line line{chip.get_line(1)};
	
	gpiod::line_request config{};
	config.request_type = gpiod::line_request::DIRECTION_OUTPUT;
	config.consumer = "Consumer";
	line.request(config);

	line.set_value(1);
	usleep(28000);

	constexpr uint32_t pin{3};
	constexpr float multiplier{18.f / (18.f + 33.f)};
	float volts{multiplier * analog_pin_volts(pin)};

	usleep(4000);
	line.set_value(0);

	return calculate_dust(volts);
}

float water_temperature()
{
	constexpr uint32_t pin_number{1};
	float voltage{analog_pin_volts(pin_number)};

	constexpr float base_degrees{25.f};
	constexpr float base_voltage{0.75f};
	constexpr float degree_volts{0.01f};
	return base_degrees + (voltage - base_voltage) / degree_volts;
}

float water_turbidity()
{
	constexpr uint32_t pin_number{0};
	constexpr float multiplier{18.f / (18.f + 33.f)};
	return calculate_turbidity(analog_pin_volts(pin_number) * multiplier);
}
