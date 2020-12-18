#ifndef JSON_H
#define JSON_H

#include "FundamentalTypes.h"
#include <string>

struct json_data
{
	std::string date;
	f32 dust;
	f32 turbidity;
	f32 temperature;
	struct
	{
		f32 humidity;
		f32 pressure;
		f32 temperature;
	} meteo_station;
};

std::string to_json(const json_data& data);

#endif