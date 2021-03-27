add_executable(
        CyberDuck
        analog_sensors.h
        analog_sensors.cpp
        encoder.h
        encoder.cpp
        main.cpp
        meteo_station.h
        meteo_station.cpp
        server.h
        server.cpp
)

target_link_libraries(
        CyberDuck PRIVATE
        gpiodcxx
        third_party::bme280
        third_party::json
        third_party::beast
)
