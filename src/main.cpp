#include "basic_sensors.h"
#include <iostream>

int main()
{
	std::cout << "Dust: " << basic_sensors::dust() << '\n';
	std::cout << "Temperature: " << basic_sensors::temperature() << '\n';
	std::cout << "Turbidity: " << basic_sensors::turbidity() << '\n';
}
