#include "analog_sensors.h"
#include "encoder.h"
#include "meteo_station.h"
#include "server.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
	// for now by default use a test provider, as the real one works only on CyberDuck
	auto provider = +[]() {
		return to_json(
		    {rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX),
		     rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX),
		     rand() / static_cast<float>(RAND_MAX), rand() / static_cast<float>(RAND_MAX)});
	};

	// use the real provider
	if (argc == 2)
	{
		provider = +[]() {
			return to_json({atmospheric_dust(), water_turbidity(), water_temperature(),
			                atmospheric_humidity(), atmospheric_pressure(),
			                atmospheric_temperature()});
		};
	}

	try
    {
        server messenger{provider};
        std::cin.get();
	}
    catch(const std::exception& e)
    {
        std::cerr << "An error has occured: " << e.what() << "\nDid you run the program as root user?\n";
        return EXIT_FAILURE;
	}
	catch(...)
    {
		std::cerr << "An unknown error has occured." << "\nDid you run the program as root user?\n";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
