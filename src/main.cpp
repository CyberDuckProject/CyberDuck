#include "sensors.h"
#include <iostream>

#include <sstream>
std::string json()
{
	std::stringstream ss;
	ss << "{\"water_temperature\":" << sensors::water_temperature() << ',';
	ss << "\"water_turbidity\":" << sensors::water_turbidity() << ',';
	ss << "\"atmospheric_dust\":" << sensors::atmospheric_dust() << '}';
	return ss.str();
}

i32 main()
{
	sensors::init();

	std::cout << "water temperature: " << sensors::water_temperature() << " C\n";
	std::cout << "water turbidity: " << sensors::water_turbidity() << " NTU\n";
	std::cout << "atmospheric dust: " << sensors::atmospheric_dust() << " ug/m3\n";

	return EXIT_SUCCESS;
}
