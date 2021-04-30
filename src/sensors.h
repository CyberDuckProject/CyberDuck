#ifndef SENSORS_H
#define SENSORS_H

#include "fundamental_types.h"
#include <gpiod.hpp>

class sensors
{
public:
	sensors();

	std::string json();

private:
	f32 atmospheric_dust();
	f32 water_temperature();
	f32 water_turbidity();

	gpiod::chip gpio_chip;
	gpiod::line dust_line;
};

#endif
