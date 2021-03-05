add_executable(
	CyberDuck
	analog_sensors.h
	analog_sensors.cpp
	main.cpp
	meteo_station.h
	meteo_station.cpp
)

target_link_libraries(
	CyberDuck PRIVATE
	gpiodcxx
	third_party::bme280
)
