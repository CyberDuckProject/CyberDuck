#include "environment.h"

#include "sensors/analog_input.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace {

std::string javascript_time()
{
	using namespace boost::posix_time;
	return to_iso_extended_string(microsec_clock::universal_time()) + 'Z';
}

} // namespace

std::string environment::json()
{
	nlohmann::json result;
	result["time"] = javascript_time();
	result["water_temperature"] = water_temperature();
	result["water_turbidity"] = water_turbidity();

	try
	{
		result["atmospheric_dust"] = dust_sensor.read();
		result["atmospheric_pressure"] = pressure_sensor.read();
	}
	catch (const std::exception& e)
	{
		spdlog::error("Sensor error: {}", e.what());
	}

	return result.dump();
}

f32 environment::water_temperature()
{
	f32 voltage{sensors::analog_pin(1)};
	return 25.f + (voltage - 0.75f) / 0.01f;
}

f32 environment::water_turbidity()
{
	f32 voltage{sensors::before_voltage_divider(sensors::analog_pin(0))};
	return -1120.4f * voltage * voltage + 5742.3f * voltage - 4352.9f;
}
