#include "analog_sensors.h"

#include <cassert>
#include <fstream>
#include <cstdint>

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

float turbidity_value(float voltage)
{
	return -1120.4f * voltage * voltage + 5742.3f * voltage - 4352.9f;
}

} // namespace

float atmospheric_dust()
{
	return 0.f;
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
	return turbidity_value(analog_pin_volts(pin_number) * multiplier);
}
