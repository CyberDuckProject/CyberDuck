#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "sensors/dust.h"
#include "sensors/pressure.h"
#include <gpiod.hpp>

class environment
{
public:
	std::string json();

private:
	f32 water_temperature();
	f32 water_turbidity();

	sensors::dust dust_sensor;
	sensors::pressure pressure_sensor;
};

#endif
