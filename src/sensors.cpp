#include "sensors.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <unistd.h>

namespace {

std::string javascript_time()
{
	using namespace boost::posix_time;
	return to_iso_extended_string(microsec_clock::universal_time()) + 'Z';
}

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

} // namespace

sensors::sensors() : gpio_chip{"gpiochip3"}
{
	gpiod::line_request config{};
	config.request_type = gpiod::line_request::DIRECTION_OUTPUT;
	config.consumer = "Consumer";

	dust_line = gpio_chip.get_line(1);
	dust_line.request(config);
	dust_line.set_value(0);
}

std::string sensors::json()
{
	nlohmann::json result;
	result["time"] = javascript_time();
	result["atmospheric_dust"] = atmospheric_dust();
	result["water_temperature"] = water_temperature();
	result["water_turbidity"] = water_turbidity();

	return result.dump();
}

f32 sensors::atmospheric_dust()
{
	f32 result{};
	for (u32 i = 0; i < 10 && result <= 0.f; ++i)
	{
		dust_line.set_value(1);
		usleep(280);
		f32 voltage = analog_pin(3);
		dust_line.set_value(0);

		voltage /= 18.f / (18.f + 33.f);
		result = (voltage - 0.6f) * 0.2f;

		usleep(10000);
	}

	if (result <= 0.f)
	{
		spdlog::error("Sensor error: dust sensor measured no dust 10 times");
		return 0.f;
	}

	return result;
}

f32 sensors::water_temperature()
{
	f32 voltage{analog_pin(1)};
	return 25.f + (voltage - 0.75f) / 0.01f;
}

f32 sensors::water_turbidity()
{
	f32 voltage{analog_pin(0)};
	voltage /= 18.f / (18.f + 33.f);
	return -1120.4f * voltage * voltage + 5742.3f * voltage - 4352.9f;
}
