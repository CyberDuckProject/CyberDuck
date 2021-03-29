#include "encoder.h"
#include <nlohmann/json.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace
{
	std::string iso_8601_time_now()
	{
        using namespace boost::posix_time;
		return to_iso_extended_string(microsec_clock::universal_time()) + 'Z';
	}
}

std::string to_json(const message& data)
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
