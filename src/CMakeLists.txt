add_executable(
    CyberDuck
    main.cpp
    fundamental_types.h
    server.h
    server.cpp
    sensors.h
    sensors.cpp
)

find_package(spdlog REQUIRED)
find_package(
    Boost REQUIRED
    COMPONENTS date_time
)
find_package(nlohmann_json REQUIRED)

target_link_libraries(
    CyberDuck PRIVATE
    spdlog::spdlog
    Boost::boost
    nlohmann_json::nlohmann_json
    Boost::date_time
    gpiodcxx
)
