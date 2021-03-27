#include "analog_sensors.h"
#include "encoder.h"
#include "meteo_station.h"
#include "server.h"
#include <chrono>
#include <thread>

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

	server messenger{provider};
	while (true)
	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(1000ms);
	}
}
