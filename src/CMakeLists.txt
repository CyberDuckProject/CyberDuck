add_executable(
    CyberDuck
    main.cpp
    fundamental_types.h
    sensors.h
    sensors.cpp
)

target_link_libraries(
    CyberDuck PRIVATE
    gpiodcxx
)

target_include_directories(CyberDuck PRIVATE .)
