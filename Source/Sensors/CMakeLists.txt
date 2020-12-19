add_library(
	Sensors STATIC
	FundamentalTypes.h
	AnalogPin.h
	AnalogPin.cpp
	Utilities.h
	Utilities.cpp
	DigitalPin.h
	DigitalPin.cpp
)

# CyberDuck namespace
add_library(CyberDuck::Sensors ALIAS Sensors)

# Include directory
target_include_directories(Sensors PUBLIC .)
