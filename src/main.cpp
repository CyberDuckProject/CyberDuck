#include "analog_sensors.h"
#include "encoder.h"
#include "meteo_station.h"
#include "server.h"
#include <chrono>
#include <thread>

int main()
{
	server messenger{[]() {
		return to_json({atmospheric_dust(), water_turbidity(), water_temperature(),
		                atmospheric_humidity(), atmospheric_pressure(), atmospheric_temperature()});
	}};
	while (true)
	{
        using namespace std::chrono_literals;
		std::this_thread::sleep_for(1000ms);
	}
}
