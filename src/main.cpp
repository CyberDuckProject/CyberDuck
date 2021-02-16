#include "analog_sensors.h"
#include "meteo_station.h"
#include <iostream>

int main()
{
	std::cout << "Analog sensors:\n";
	std::cout << "  Atmospheric dust: " << atmospheric_dust() << '\n';
	std::cout << "  Water temperature: " << water_temperature() << '\n';
	std::cout << "  Water turbidity: " << water_turbidity() << '\n';

	std::cout << "Meteo station:\n";
	std::cout << "  Atmospheric temperature: " << atmospheric_temperature() << '\n';
	std::cout << "  Atmospheric humidity: " << atmospheric_humidity() << '\n';
	std::cout << "  Atmospheric pressure: " << atmospheric_pressure() << '\n';
}
