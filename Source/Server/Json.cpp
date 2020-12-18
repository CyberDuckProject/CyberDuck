#include "Json.h"

#include <ctime>
#include <nlohmann/json.hpp>

namespace
{
	std::string iso_8601_time_now()
	{
		std::time_t now;
		std::time(&now);
		char buffer[25];
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", std::gmtime(&now));
		return std::string{buffer};
	}
}

std::string to_json(const json_data& data)
{
	nlohmann::json json{};
	json["date"] = iso_8601_time_now();
	json["dust"] = data.dust;
	json["turbidity"] = data.turbidity;
	json["temperature"] = data.temperature;
	json["meteoStation"]["humidity"] = data.meteo_station.humidity;
	json["meteoStation"]["pressure"] = data.meteo_station.pressure;
	json["meteoStation"]["temperature"] = data.meteo_station.temperature;
	return json.dump();
}