#include "basic_sensors.h"
#include "meteo_station.h"
#include <iostream>

int main()
{
	std::cout << "Basic sensors:\n";
	std::cout << "  Dust: " << basic_sensors::dust() << '\n';
	std::cout << "  Temperature: " << basic_sensors::temperature() << '\n';
	std::cout << "  Turbidity: " << basic_sensors::turbidity() << '\n';

	std::cout << "Meteo station:\n";
	std::cout << "  Temperature: " << meteo_station::temperature() << '\n';
	std::cout << "  Humidity: " << meteo_station::humidity() << '\n';
	std::cout << "  Pressure: " << meteo_station::pressure() << '\n';
}
