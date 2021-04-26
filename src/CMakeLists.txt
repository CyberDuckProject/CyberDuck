add_executable(
    CyberDuck
    main.cpp
    fundamental_types.h
    server.h
    server.cpp
)

find_package(spdlog REQUIRED)
find_package(Boost REQUIRED)

target_link_libraries(
    CyberDuck PRIVATE
    spdlog::spdlog
    Boost::boost
)
